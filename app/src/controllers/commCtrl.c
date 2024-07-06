/**
 * @file commCtrl.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-07-06
 *
 * @copyright Copyright (c) 2024
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "commCtrl.h"
#include "usartDrv.h"
#include <string.h>
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define START_BYTE '#'
#define END_BYTE '$'
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
usartDrv_t u1;
usartComm_t u1Comm;
/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

void commCtrlRun(void)
{
    if (udRx(&u1, &u1Comm.buff[u1Comm.idx]))
    {
        if (u1Comm.idx > 0)
        {
            if (u1Comm.buff[u1Comm.idx] == END_BYTE)
            {
                commCtrlCmd(u1Comm.buff[1], u1Comm.buff[2]);
                memset(&u1Comm, 0, sizeof(u1Comm));
            }
            else
            {
                u1Comm.idx++;
            }
        }
        else if (u1Comm.buff[u1Comm.idx] == START_BYTE)
        {
            u1Comm.idx++;
            return;
        }
    }
}

void commCtrlCmd(opCode_t cmd, uint8_t *data)
{
    switch (cmd)
    {
    case CMD_PING:
    {
        enqueue(&u1.tx, START_BYTE);
        enqueue(&u1.tx, CMD_PONG);
        enqueue(&u1.tx, END_BYTE);
        while (udTx(&u1))
        {
        };

        break;
    }

    case CMD_PONG:
    {
        enqueue(&u1.tx, START_BYTE);
        enqueue(&u1.tx, CMD_PING);
        enqueue(&u1.tx, END_BYTE);
        while (udTx(&u1))
        {
        };

        break;
    }

    default:
        break;
    }
}

void commCtrlInit(void)
{
    udInit(&u1, DRV_USART1);
    memset(&u1Comm, 0, sizeof(u1Comm));
}
