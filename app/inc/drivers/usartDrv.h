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
#include <stdbool.h>

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
    uint8_t rxSize;
    uint8_t txSize;
    uint32_t txTimeout;
    uint32_t rxTimeout;
    uint8_t rxBuff[16];
    uint8_t txBuff[16];
    Queue rxQueue;
} usartDrv_t;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void udInit(usartDrv_t *self, uInst instance);
void udDefConf(usartDrv_t *self);
uint8_t udRxIT(usartDrv_t *self);
uint8_t udRxBlck(usartDrv_t *self);
uint8_t udRxDMA(usartDrv_t *self);
uint8_t udTxIT(usartDrv_t *self);
uint8_t udTxBlck(usartDrv_t *self);
uint8_t udTxDMA(usartDrv_t *self);

/* Private defines -----------------------------------------------------------*/

#endif /* __USARTDRV_H */
