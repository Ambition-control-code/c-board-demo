#ifndef BSP_EXTI_H
#define BSP_EXTI_H

#include "bsp.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    BSP_EXTI_INT1_ACCEL = 0U, /* PC4, BMI088 accelerometer DRDY */
    BSP_EXTI_INT1_GYRO,       /* PC5, BMI088 gyroscope DRDY      */
    BSP_EXTI_KEY,             /* PA0, user key                   */
    BSP_EXTI_NUM
} BSP_EXTI_Source_e;

/* Called in the EXTI interrupt. Keep it short, e.g. signal an acquisition task. */
typedef void (*BSP_EXTI_Callback)(BSP_EXTI_Source_e source);

/* One callback per source. Pass NULL to unregister that source. */
Status_e BSP_EXTI_RegisterCallback(BSP_EXTI_Source_e source, BSP_EXTI_Callback callback);

#ifdef __cplusplus
}
#endif

#endif
