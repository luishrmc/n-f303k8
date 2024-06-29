/**
 * @file uartDriver.c
 * @author luis (luishenrique.8804@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-06-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "uartDriver.h"
#include <stdlib.h>
#include "stm32f3xx_hal.h"
#include "stm32f303x8.h"

#define USART2_RX GPIO_PIN_2
#define USART2_TX GPIO_PIN_15
#define USART2_PORT GPIOA
#define PRINTF_TRACE int __io_putchar(int ch)

UART_HandleTypeDef huart2;
uint8_t *uRxData1;
uint8_t *uRxData2;

// declaração da macro offsetof
#define offsetof(TYPE, MEMBER) ((size_t) & ((TYPE *)0)->MEMBER)

// declaração da macro container_of
#define container_of(ptr, type, member) ({            \
 const __typeof( ((type *)0)->member ) *__mptr = (ptr);    \
 (type *)( (char *)__mptr - offsetof(type,member) ); })

void udInit(uartDriver_t *self, uInst instance)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    memset(self, 0, sizeof(uartDriver_t));
    initQueue(&self->rx);
    initQueue(&self->tx);
    self->inst = instance;

    switch (instance)
    {

    case UART1:
    {
        break;
    }

    case UART2:
    {
        __HAL_RCC_USART2_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

        GPIO_InitStruct.Pin = USART2_TX | USART2_RX;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
        HAL_GPIO_Init(USART2_PORT, &GPIO_InitStruct);

        huart2.Instance = USART2;
        huart2.Init.BaudRate = 115200;
        huart2.Init.WordLength = UART_WORDLENGTH_8B;
        huart2.Init.StopBits = UART_STOPBITS_1;
        huart2.Init.Parity = UART_PARITY_NONE;
        huart2.Init.Mode = UART_MODE_TX_RX;
        huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
        huart2.Init.OverSampling = UART_OVERSAMPLING_16;
        huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
        huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
        if (HAL_UART_Init(&huart2) != HAL_OK)
        {
            Error_Handler();
        }

        HAL_NVIC_SetPriority(USART2_IRQn, 6, 0);
        HAL_NVIC_EnableIRQ(USART2_IRQn);

        uRxData2 = &self->rxData;
        HAL_UART_Receive_IT(&huart2, &self->rxData, 1);
        break;
    }

    default:
        break;
    }
}

void udTx(uartDriver_t *self)
{
    uint8_t data;
    switch (self->inst)
    {
    case UART1:
    {
        break;
    }

    case UART2:
    {
        if (dequeue(&self->tx, &data) == 1)
            HAL_UART_Transmit(&huart2, (uint8_t *)&data, 1, 0xFFFF);
        break;
    }

    default:
        break;
    }
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(huart);

    if (huart->Instance == USART2)
    {
        uartDriver_t *uart;
        uart = container_of(uRxData2, uartDriver_t, rxData);
        enqueue(&uart->rx, uart->rxData);
        HAL_UART_Receive_IT(&huart2, &uart->rxData, 1);
    }
}

/**
 * @brief  Retargets the C library printf function to the USART.
 * @param  None
 * @retval None
 */
PRINTF_TRACE
{
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
}