/**
 * @file uartDriver.h
 * @author luis (luishenrique.8804@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-06-29
 *
 * @copyright Copyright (c) 2024
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USARTDRV_H
#define __USARTDRV_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "queue.h"
/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef enum
{
    DRV_USART1,
    DRV_USART2
} uInst;

typedef struct
{
    uInst inst;
    uint8_t rxData;
    Queue rx;
    Queue tx;
} usartDrv_t;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void udInit(usartDrv_t *self, uInst instance);
uint8_t udTx(usartDrv_t *self);
uint8_t udRx(usartDrv_t *self, uint8_t *data);

/* Private defines -----------------------------------------------------------*/

#endif /* __USARTDRV_H */
