#include "bsp_exti.h"
#include "main.h"
#include <stdatomic.h>

static _Atomic(BSP_EXTI_Callback) callbacks[BSP_EXTI_NUM];

Status_e BSP_EXTI_RegisterCallback(BSP_EXTI_Source_e source, BSP_EXTI_Callback callback)
{
    if ((unsigned)source >= BSP_EXTI_NUM)
    {
        return STATUS_INVALID_PARAM;
    }

    atomic_store_explicit(&callbacks[source], callback, memory_order_release);
    return STATUS_OK;
}

void HAL_GPIO_EXTI_Callback(uint16_t pin)
{
    BSP_EXTI_Source_e source;
    switch (pin)
    {
        case INT1_Accel_Pin: source = BSP_EXTI_INT1_ACCEL; break;
        case INT1_Gyro_Pin:  source = BSP_EXTI_INT1_GYRO;  break;
        case KEY_Pin:        source = BSP_EXTI_KEY;        break;
        default: return;
    }

    BSP_EXTI_Callback callback = atomic_load_explicit(&callbacks[source], memory_order_acquire);
    if (callback != NULL)
    {
        callback(source);
    }
}
