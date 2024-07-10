/**
 * @file commCtrl.h
 * @author your name (you@domain.com)
 * @brief
 * @version 1.0
 * @date 2024-07-07
 *
 * @copyright Copyright (c) 2024
 *
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMMCTRL_H
#define __COMMCTRL_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "queue.h"
#include "usartDrv.h"
#include "spiDrv.h"

/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

typedef enum
{
    CMD_PING = 0x31,
    CMD_PONG = 0x32
} opCode_t;

typedef struct
{
    uint8_t idx;
    uint8_t cmd[16];
    usartDrv_t u1;
    spiDrv_t s1;
} comm_t;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void commCtrlInit(void);
void commCtrlRunUSART(void);
void commCtrlCmdUSART(comm_t *self, opCode_t cmd, uint8_t *data);

void commCtrlRunSPI(void);
void commCtrlCmdSPI(comm_t *self, opCode_t cmd, uint8_t *data);

/* Private defines -----------------------------------------------------------*/

#endif /* __COMMCTRL_H */
