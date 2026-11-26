#ifndef BSP_GPIO_H
#define BSP_GPIO_H

#include "main.h"
#include "stm32f4xx_hal.h"

#include "bsp.h"

typedef enum
{
    BSP_GPIO_BMI088_ACCEL_CS = 0U, /* PA4; configure output in CubeMX first. */
    BSP_GPIO_BMI088_GYRO_CS,       /* PB0; configure output in CubeMX first. */
    BSP_GPIO_USER_KEY,             /* PA0; input, EXTI0 rising/falling. Read only. */
    BSP_GPIO_BMI088_ACCEL_INT1,    /* PC4; input, EXTI4 rising. Read only. */
    BSP_GPIO_BMI088_GYRO_INT1,     /* PC5; input, EXTI9_5 rising. Read only. */
    BSP_GPIO_NUM,
} BSP_GPIO_Id_e;

typedef struct
{
    GPIO_TypeDef *port;
    uint16_t pin;
} BSP_GPIO_Pin_t;

Status_e BSP_GPIO_Set(BSP_GPIO_Id_e id, bool level);
Status_e BSP_GPIO_Get(BSP_GPIO_Id_e id, bool *level);

#endif
