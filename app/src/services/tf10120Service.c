/**
 * @file tf10120Service.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2024-06-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "tf10120Service.h"
#include "uartDriver.h"
#include <stdio.h>

uartDriver_t disSensor;

void tfsInit(void)
{
    udInit(&disSensor, UART1);
}

void tfsSet(setCommands_t cmd, uint16_t data)
{
    char str[8];
    sprintf(str, "%d", data);

    enqueue(&disSensor.tx, 's');
    if (cmd == sPOS_DEV)
    {
        enqueue(&disSensor.tx, (cmd + 48));
        enqueue(&disSensor.tx, '+');
    }
    else
    {
        enqueue(&disSensor.tx, (cmd + 47));
        enqueue(&disSensor.tx, '-');
    }

    for (uint8_t i = 0; str[i] != '\0'; i++)
    {
        enqueue(&disSensor.tx, str[i]);
    }
    enqueue(&disSensor.tx, '#');

    while (udTx(&disSensor))
    {
    }
}

uint16_t tfsRead(readCommands_t cmd)
{
    enqueue(&disSensor.tx, 'r');
    enqueue(&disSensor.tx, (cmd + 48));
    enqueue(&disSensor.tx, '#');

    while (udTx(&disSensor))
    {
    }
}

char dist[8];
uint8_t data;
int8_t flag = -1;
uint16_t tfsGetDist(void)
{
    while (udRx(&disSensor, &data))
    {
        if (data == '\n')
        {
            flag = 0;
            continue;
        }

        if (flag >= 0)
        {
            if (flag < 5)
                dist[flag++] = data;
            else
            {
                printf("%s\r\n", dist);
                memset(dist, 0, sizeof(dist));
                flag = -1;
            }
        }
    }
}