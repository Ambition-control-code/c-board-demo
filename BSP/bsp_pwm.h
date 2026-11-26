#ifndef BSP_PWM_H
#define BSP_PWM_H

#include "tim.h"
#include "stm32f4xx_hal.h"

#include "bsp.h"

typedef enum
{
    BSP_PWM_TIM5_CH1 = 0U, /* PH10: blue LED */
    BSP_PWM_TIM5_CH2,      /* PH11: green LED */
    BSP_PWM_TIM5_CH3,      /* PH12: red LED */
    BSP_PWM_TIM10_CH1,     /* PB8 */
    BSP_PWM_TIM1_CH1,      /* PE9:  servo 1, 50 Hz  */
    BSP_PWM_TIM1_CH2,      /* PE11: servo 2, 50 Hz  */
    BSP_PWM_TIM1_CH3,      /* PE13: servo 3, 50 Hz  */
    BSP_PWM_TIM1_CH4,      /* PE14: servo 4, 50 Hz  */
    BSP_PWM_TIM8_CH1,      /* PC6:  servo 5, 50 Hz  */
    BSP_PWM_TIM8_CH2,      /* PI6:  servo 6, 50 Hz  */
    BSP_PWM_TIM8_CH3,      /* PI7:  servo 7, 50 Hz  */
    BSP_PWM_TIM3_CH3,      /* PC8:  5V laser, 1 kHz */
    BSP_PWM_TIM4_CH3,      /* PD14: buzzer, 4 kHz   */
    BSP_PWM_NUM,
} BSP_PWM_Channel_e;

typedef struct
{
    TIM_HandleTypeDef *handle;
    uint32_t channel;
} BSP_PWM_Channel_t;

Status_e BSP_PWM_Start(BSP_PWM_Channel_e channel);
Status_e BSP_PWM_Stop(BSP_PWM_Channel_e channel);
Status_e BSP_PWM_SetCompare(BSP_PWM_Channel_e channel, uint32_t compare);

#endif
