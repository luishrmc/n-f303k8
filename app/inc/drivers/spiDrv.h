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
    uint8_t tx[16];
    uint8_t rx[16];
    uint8_t size;
} spiDrv_t;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void sdInit(spiDrv_t *self, sInst instance);
uint8_t sdInOut(spiDrv_t *self);
uint8_t sdIn(spiDrv_t *self, sInst *data);
uint8_t sdOut(spiDrv_t *self);
uint8_t sdNss(sNss_t slave);

/* Private defines -----------------------------------------------------------*/

#endif /* __SPIDRV_H */
