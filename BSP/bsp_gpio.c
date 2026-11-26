#include "bsp_gpio.h"

static const BSP_GPIO_Pin_t gpio_pins[BSP_GPIO_NUM] =
{
    [BSP_GPIO_BMI088_ACCEL_CS]  = {GPIOA, GPIO_PIN_4},
    [BSP_GPIO_BMI088_GYRO_CS]   = {GPIOB, GPIO_PIN_0},
    [BSP_GPIO_USER_KEY]         = {GPIOA, GPIO_PIN_0},
    [BSP_GPIO_BMI088_ACCEL_INT1] = {GPIOC, GPIO_PIN_4},
    [BSP_GPIO_BMI088_GYRO_INT1]  = {GPIOC, GPIO_PIN_5},
};

Status_e BSP_GPIO_Set(BSP_GPIO_Id_e id, bool level)
{
    if ((uint32_t)id >= BSP_GPIO_NUM)
    {
        return STATUS_INVALID_PARAM;
    }

    HAL_GPIO_WritePin(gpio_pins[id].port,
                      gpio_pins[id].pin,
                      level ? GPIO_PIN_SET : GPIO_PIN_RESET);
    return STATUS_OK;
}

Status_e BSP_GPIO_Get(BSP_GPIO_Id_e id, bool *level)
{
    if ((uint32_t)id >= BSP_GPIO_NUM || level == NULL)
    {
        return STATUS_INVALID_PARAM;
    }

    *level = (HAL_GPIO_ReadPin(gpio_pins[id].port, gpio_pins[id].pin) == GPIO_PIN_SET);
    return STATUS_OK;
}
