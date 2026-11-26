#include "bsp_pwm.h"

static BSP_PWM_Channel_t pwm_channels[BSP_PWM_NUM] =
{
    [BSP_PWM_TIM5_CH1] = {.handle = &htim5, .channel = TIM_CHANNEL_1},
    [BSP_PWM_TIM5_CH2] = {.handle = &htim5, .channel = TIM_CHANNEL_2},
    [BSP_PWM_TIM5_CH3] = {.handle = &htim5, .channel = TIM_CHANNEL_3},
    [BSP_PWM_TIM10_CH1] = {.handle = &htim10, .channel = TIM_CHANNEL_1},
    [BSP_PWM_TIM1_CH1] = {.handle = &htim1, .channel = TIM_CHANNEL_1},
    [BSP_PWM_TIM1_CH2] = {.handle = &htim1, .channel = TIM_CHANNEL_2},
    [BSP_PWM_TIM1_CH3] = {.handle = &htim1, .channel = TIM_CHANNEL_3},
    [BSP_PWM_TIM1_CH4] = {.handle = &htim1, .channel = TIM_CHANNEL_4},
    [BSP_PWM_TIM8_CH1] = {.handle = &htim8, .channel = TIM_CHANNEL_1},
    [BSP_PWM_TIM8_CH2] = {.handle = &htim8, .channel = TIM_CHANNEL_2},
    [BSP_PWM_TIM8_CH3] = {.handle = &htim8, .channel = TIM_CHANNEL_3},
    [BSP_PWM_TIM3_CH3] = {.handle = &htim3, .channel = TIM_CHANNEL_3},
    [BSP_PWM_TIM4_CH3] = {.handle = &htim4, .channel = TIM_CHANNEL_3},
};

Status_e BSP_PWM_Start(BSP_PWM_Channel_e channel)
{
    if (channel >= BSP_PWM_NUM)
    {
        return STATUS_INVALID_PARAM;
    }

    if (HAL_TIM_PWM_Start(pwm_channels[channel].handle,
                          pwm_channels[channel].channel) != HAL_OK)
    {
        return STATUS_ERROR;                                                                                                                                        
    }

    return STATUS_OK;
}

Status_e BSP_PWM_Stop(BSP_PWM_Channel_e channel)
{
    if (channel >= BSP_PWM_NUM)
    {
        return STATUS_INVALID_PARAM;
    }

    if (HAL_TIM_PWM_Stop(pwm_channels[channel].handle,
                         pwm_channels[channel].channel) != HAL_OK)
    {
        return STATUS_ERROR;
    }

    return STATUS_OK;
}

Status_e BSP_PWM_SetCompare(BSP_PWM_Channel_e channel, uint32_t compare)
{
    if (channel >= BSP_PWM_NUM)
    {
        return STATUS_INVALID_PARAM;
    }

    __HAL_TIM_SET_COMPARE(pwm_channels[channel].handle,
                          pwm_channels[channel].channel,
                          compare);
    return STATUS_OK;
}
