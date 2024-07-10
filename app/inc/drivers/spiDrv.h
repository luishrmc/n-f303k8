/**
 * @file spiDrv.h
 * @author luis (luishenrique.8804@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-07-05
 *
 * @copyright Copyright (c) 2024
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPIDRV_H
#define __SPIDRV_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "queue.h"
/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef enum
{
    DRV_SPI1,
} sInst;

typedef enum
{
    SLAVE1_SET,
    SLAVE1_RESET
} sNss_t;

typedef struct
{
    sInst inst;
    sNss_t slave;
    uint8_t rxSize;
    uint8_t txSize;
    uint32_t txTimeout;
    uint32_t rxTimeout;
    uint8_t rxBuff[16];
    uint8_t txBuff[16];
    Queue rxQueue;
} spiDrv_t;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void sdInit(spiDrv_t *self, sInst instance);
void sdDefConf(spiDrv_t *self);
uint8_t sdInOutBlck(spiDrv_t *self);
uint8_t sdInBlck(spiDrv_t *self);
uint8_t sdOutBlck(spiDrv_t *self);
uint8_t sdInOutIT(spiDrv_t *self);
uint8_t sdInIT(spiDrv_t *self);
uint8_t sdOutIT(spiDrv_t *self);
uint8_t sdNss(sNss_t slave);

/* Private defines -----------------------------------------------------------*/

#endif /* __SPIDRV_H */
