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
comm_t comm;

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

void commCtrlRunUSART(void)
{
    while (dequeue(&comm.u1.rxQueue, &comm.cmd[comm.idx]))
    {
        if (comm.idx > 0)
        {
            if (comm.cmd[comm.idx] == END_BYTE)
            {
                commCtrlCmdUSART(&comm, comm.cmd[1], &comm.cmd[2]);
                memset(&comm.cmd, 0, sizeof(comm.cmd));
                comm.idx = 0;
            }
            else
            {
                comm.idx++;
            }
        }
        else if (comm.cmd[comm.idx] == START_BYTE)
        {
            comm.idx++;
            continue;
        }
    }
}

void commCtrlCmdUSART(comm_t *self, opCode_t cmd, uint8_t *data)
{
    switch (cmd)
    {
    case CMD_PING:
    {
        self->u1.txBuff[0] = START_BYTE;
        self->u1.txBuff[1] = CMD_PONG;
        self->u1.txBuff[2] = END_BYTE;
        self->u1.txSize = 3;
        // udTxBlck(&self->u1);
        // udTxIT(&self->u1);
        udTxDMA(&self->u1);
        break;
    }

    case CMD_PONG:
    {
        self->u1.txBuff[0] = START_BYTE;
        self->u1.txBuff[1] = CMD_PING;
        self->u1.txBuff[2] = END_BYTE;
        self->u1.txSize = 3;
        // udTxBlck(&self->u1);
        // udTxIT(&self->u1);
        udTxDMA(&self->u1);
        break;
    }

    default:
        break;
    }
}

void commCtrlRunSPI(void)
{
    while (dequeue(&comm.s1.rxQueue, &comm.cmd[comm.idx]))
    {
        if (comm.idx > 0)
        {
            if (comm.cmd[comm.idx] == END_BYTE)
            {
                commCtrlCmdSPI(&comm, comm.cmd[1], &comm.cmd[2]);
                memset(&comm.cmd, 0, sizeof(comm.cmd));
                comm.idx = 0;
            }
            else
            {
                comm.idx++;
            }
        }
        else if (comm.cmd[comm.idx] == START_BYTE)
        {
            comm.idx++;
            continue;
        }
    }
}

void commCtrlCmdSPI(comm_t *self, opCode_t cmd, uint8_t *data)
{
    switch (cmd)
    {
    case CMD_PING:
    {
        self->s1.txBuff[0] = START_BYTE;
        self->s1.txBuff[1] = CMD_PONG;
        self->s1.txBuff[2] = END_BYTE;
        self->s1.txSize = 3;
        printf("PONG\n");
        // dOutBlck(&self.s1);
        sdOutIT(&self->s1);
        break;
    }

    case CMD_PONG:
    {
        self->s1.txBuff[0] = START_BYTE;
        self->s1.txBuff[1] = CMD_PING;
        self->s1.txBuff[2] = END_BYTE;
        self->s1.txSize = 3;
        printf("PING\n");
        // sdOutBlck(&self.s1);
        sdOutIT(&self->s1);
        break;
    }

    default:
        break;
    }
}

void commCtrlInit(void)
{
    memset(&comm, 0, sizeof(comm_t));
    sdInit(&comm.s1, DRV_SPI1);

    comm.s1.txBuff[0] = START_BYTE;
    comm.s1.txBuff[1] = CMD_PING;
    comm.s1.txBuff[2] = END_BYTE;
    comm.s1.txSize = 3;
    comm.s1.rxSize = 3;

    sdNss(SLAVE1_RESET);
    sdOutBlck(&comm.s1);
    sdInBlck(&comm.s1);
    sdNss(SLAVE1_SET);
}
