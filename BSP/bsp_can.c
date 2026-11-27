#include "bsp_can.h"

static BSP_CAN_Channel_t can_channels[BSP_CAN_NUM] =
{
    [BSP_CAN_1] = {.bus = BSP_CAN_1, .handle = &hcan1},
    [BSP_CAN_2] = {.bus = BSP_CAN_2, .handle = &hcan2},
};

static BSP_CAN_Channel_t *CAN_GetChannelByHandle(CAN_HandleTypeDef *hcan)
{
    for (uint8_t i = 0U; i < BSP_CAN_NUM; i++)
    {
        if (can_channels[i].handle == hcan)
        {
            return &can_channels[i];
        }
    }
    return NULL;
}

static Status_e CAN_ConfigureRx(BSP_CAN_Channel_t *channel)
{
    CAN_FilterTypeDef filter = {0};

    /* bxCAN1/2 share 28 banks. Keep the CAN2 boundary at bank 14.
     * Accept all standard data IDs, rejecting extended and remote frames.
     * C_Board has RX0/RX1 IRQs, but no CAN SCE IRQ configured.
     */
    filter.FilterBank = (channel->bus == BSP_CAN_1) ? 0U : 14U;
    filter.SlaveStartFilterBank = 14U;
    filter.FilterMode = CAN_FILTERMODE_IDMASK;
    filter.FilterScale = CAN_FILTERSCALE_32BIT;
    filter.FilterIdHigh = 0U;
    filter.FilterIdLow = 0U;
    filter.FilterMaskIdHigh = 0U;
    filter.FilterMaskIdLow = CAN_ID_EXT | CAN_RTR_REMOTE;
    filter.FilterFIFOAssignment = CAN_FILTER_FIFO0;
    filter.FilterActivation = ENABLE;

    return (HAL_CAN_ConfigFilter(channel->handle, &filter) == HAL_OK)
               ? STATUS_OK : STATUS_ERROR;
}

Status_e BSP_CAN_Init(BSP_CAN_Bus_e bus, BSP_CAN_RxCallback callback)
{
    BSP_CAN_Channel_t *channel;

    if ((uint32_t)bus >= BSP_CAN_NUM || can_channels[bus].handle == NULL)
    {
        return STATUS_INVALID_PARAM;
    }
    channel = &can_channels[bus];
    channel->rx_callback = callback;
    if (channel->started)
    {
        return STATUS_OK;
    }
    if (CAN_ConfigureRx(channel) != STATUS_OK ||
        HAL_CAN_Start(channel->handle) != HAL_OK)
    {
        return STATUS_ERROR;
    }

    channel->started = true;
    if (HAL_CAN_ActivateNotification(channel->handle,
                                    CAN_IT_RX_FIFO0_MSG_PENDING |
                                    CAN_IT_RX_FIFO1_MSG_PENDING) != HAL_OK)
    {
        channel->started = false;
        (void)HAL_CAN_Stop(channel->handle);
        return STATUS_ERROR;
    }
    return STATUS_OK;
}

Status_e BSP_CAN_Send(BSP_CAN_Bus_e bus, uint32_t std_id, const uint8_t *data, uint8_t len)
{
    CAN_TxHeaderTypeDef tx_header = {0};
    uint32_t mailbox;

    if ((uint32_t)bus >= BSP_CAN_NUM || can_channels[bus].started == false || data == NULL || len > 8U)
    {
        return STATUS_INVALID_PARAM;
    }

    tx_header.StdId = std_id;
    tx_header.IDE = CAN_ID_STD;
    tx_header.RTR = CAN_RTR_DATA;
    tx_header.DLC = len;
    tx_header.TransmitGlobalTime = DISABLE;

    if (HAL_CAN_AddTxMessage(can_channels[bus].handle, &tx_header,
                            (uint8_t *)data, &mailbox) != HAL_OK)
    {
        return STATUS_BUSY;
    }
    return STATUS_OK;
}

static void CAN_RxFifoHandler(BSP_CAN_Channel_t *channel, uint32_t fifo)
{
    if (channel == NULL)
    {
        return;
    }

    HAL_CAN_GetRxMessage(channel->handle, fifo, &channel->rx_header, channel->rx_data);
    if (channel->started && channel->rx_callback != NULL && channel->rx_header.DLC <= 8U)
    {
        channel->rx_callback(channel->bus, channel->rx_header.StdId, channel->rx_data, (uint8_t)channel->rx_header.DLC);
    } 
}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    CAN_RxFifoHandler(CAN_GetChannelByHandle(hcan), CAN_RX_FIFO0);
}

void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan)
{
    CAN_RxFifoHandler(CAN_GetChannelByHandle(hcan), CAN_RX_FIFO1);
}
