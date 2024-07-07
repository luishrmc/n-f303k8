/**
 * @file commCtrl.c
 * @author your name (you@domain.com)
 * @brief
 * @version 1.0
 * @date 2024-07-07
 *
 * @copyright Copyright (c) 2024
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "commCtrl.h"
#include <string.h>

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define START_BYTE '#'
#define END_BYTE '$'
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
comm_t u1Comm;
/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

void commCtrlRun(void)
{
    while (dequeue(&u1Comm.u1.rxQueue, &u1Comm.cmd[u1Comm.idx]))
    {
        if (u1Comm.idx > 0)
        {
            if (u1Comm.cmd[u1Comm.idx] == END_BYTE)
            {
                commCtrlCmd(&u1Comm, u1Comm.cmd[1], &u1Comm.cmd[2]);
                memset(&u1Comm.cmd, 0, sizeof(u1Comm.cmd));
                u1Comm.idx = 0;
            }
            else
            {
                u1Comm.idx++;
            }
        }
        else if (u1Comm.cmd[u1Comm.idx] == START_BYTE)
        {
            u1Comm.idx++;
            continue;
        }
    }
}

void commCtrlCmd(comm_t *self, opCode_t cmd, uint8_t *data)
{
    switch (cmd)
    {
    case CMD_PING:
    {
        self->u1.txBuff[0] = START_BYTE;
        self->u1.txBuff[1] = CMD_PONG;
        self->u1.txBuff[2] = END_BYTE;
        self->u1.txSize = 3;
        self->u1.rxSize = 3;
        // udTxBlck(&self->u1);
        udTxIT(&self->u1);
        break;
    }

    case CMD_PONG:
    {
        self->u1.txBuff[0] = START_BYTE;
        self->u1.txBuff[1] = CMD_PING;
        self->u1.txBuff[2] = END_BYTE;
        self->u1.txSize = 3;
        // udTxBlck(&self->u1);
        udTxIT(&self->u1);
        break;
    }

    default:
        break;
    }
}

void commCtrlInit(void)
{
    memset(&u1Comm, 0, sizeof(comm_t));
    udInit(&u1Comm.u1, DRV_USART1);

    u1Comm.u1.txBuff[0] = START_BYTE;
    u1Comm.u1.txBuff[1] = CMD_PING;
    u1Comm.u1.txBuff[2] = END_BYTE;
    u1Comm.u1.txSize = 3;
    udTxBlck(&u1Comm.u1);
}
