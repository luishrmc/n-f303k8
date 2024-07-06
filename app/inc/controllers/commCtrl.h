/**
 * @file commCtrl.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-07-06
 *
 * @copyright Copyright (c) 2024
 *
 */


/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMMCTRL_H
#define __COMMCTRL_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
/* Private includes ----------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

typedef enum
{
    CMD_PING = 0x31,
    CMD_PONG = 0x32
} opCode_t;

typedef struct
{
    uint8_t buff[16];
    uint8_t idx;
} usartComm_t;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void commCtrlInit(void);
void commCtrlRun(void);
void commCtrlCmd(opCode_t cmd, uint8_t* data);

/* Private defines -----------------------------------------------------------*/

#endif /* __COMMCTRL_H */
