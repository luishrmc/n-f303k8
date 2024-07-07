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

/* Includes ------------------------------------------------------------------*/
#include "usartDrv.h"
#include "mainCtrl.h"
#include <stdlib.h>
#include "stm32f3xx_hal.h"
#include "stm32f303x8.h"
#include <string.h>

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define USART1_RX GPIO_PIN_10
#define USART1_TX GPIO_PIN_9
#define USART1_PORT GPIOA

#define USART2_RX GPIO_PIN_2
#define USART2_TX GPIO_PIN_15
#define USART2_PORT GPIOA
/* Private macro -------------------------------------------------------------*/
#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

// declaração da macro OFFSETOF
#define OFFSETOF(TYPE, MEMBER) ((size_t) & ((TYPE *)0)->MEMBER)

// declaração da macro CONTAINER_OF
#define CONTAINER_OF(ptr, type, member) ({            \
 const __typeof( ((type *)0)->member ) *__mptr = (ptr);    \
 (type *)( (char *)__mptr - OFFSETOF(type,member) ); })

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
uInst *uInst1;
uInst *uInst2;
DMA_HandleTypeDef hdma_usart2_rx;
DMA_HandleTypeDef hdma_usart2_tx;

/* Private function prototypes -----------------------------------------------*/
PUTCHAR_PROTOTYPE
{
    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);
    return ch;
}

/* Private user code ---------------------------------------------------------*/

void udInit(usartDrv_t *self, uInst instance)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    memset(self, 0, sizeof(usartDrv_t));
    initQueue(&self->rxQueue);
    self->inst = instance;
    udDefConf(self);

    switch (instance)
    {

    case DRV_USART1:
    {
        __HAL_RCC_USART1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

        GPIO_InitStruct.Pin = USART1_TX | USART1_RX;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
        HAL_GPIO_Init(USART1_PORT, &GPIO_InitStruct);

        huart1.Instance = USART1;
        huart1.Init.BaudRate = 115200;
        huart1.Init.WordLength = UART_WORDLENGTH_8B;
        huart1.Init.StopBits = UART_STOPBITS_1;
        huart1.Init.Parity = UART_PARITY_NONE;
        huart1.Init.Mode = UART_MODE_TX_RX;
        huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
        huart1.Init.OverSampling = UART_OVERSAMPLING_16;
        huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
        huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
        if (HAL_UART_Init(&huart1) != HAL_OK)
        {
            Error_Handler();
        }

        HAL_NVIC_SetPriority(USART1_IRQn, 6, 0);
        HAL_NVIC_EnableIRQ(USART1_IRQn);
        uInst1 = &self->inst;
        udRxIT(self);
        break;
    }

    case DRV_USART2:
    {
        __HAL_RCC_USART2_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();
        __HAL_RCC_DMA1_CLK_ENABLE();

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

        /* USART2 DMA Init */
        /* USART2_RX Init */
        hdma_usart2_rx.Instance = DMA1_Channel6;
        hdma_usart2_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
        hdma_usart2_rx.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_usart2_rx.Init.MemInc = DMA_MINC_ENABLE;
        hdma_usart2_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_usart2_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        hdma_usart2_rx.Init.Mode = DMA_NORMAL;
        hdma_usart2_rx.Init.Priority = DMA_PRIORITY_LOW;
        if (HAL_DMA_Init(&hdma_usart2_rx) != HAL_OK)
        {
            Error_Handler();
        }

        __HAL_LINKDMA(&huart2, hdmarx, hdma_usart2_rx);

        /* USART2_TX Init */
        hdma_usart2_tx.Instance = DMA1_Channel7;
        hdma_usart2_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
        hdma_usart2_tx.Init.PeriphInc = DMA_PINC_DISABLE;
        hdma_usart2_tx.Init.MemInc = DMA_MINC_ENABLE;
        hdma_usart2_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_usart2_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        hdma_usart2_tx.Init.Mode = DMA_NORMAL;
        hdma_usart2_tx.Init.Priority = DMA_PRIORITY_LOW;
        if (HAL_DMA_Init(&hdma_usart2_tx) != HAL_OK)
        {
            Error_Handler();
        }

        __HAL_LINKDMA(&huart2, hdmatx, hdma_usart2_tx);

        /* DMA1_Channel6_IRQn interrupt configuration */
        HAL_NVIC_SetPriority(DMA1_Channel6_IRQn, 6, 0);
        HAL_NVIC_EnableIRQ(DMA1_Channel6_IRQn);
        /* DMA1_Channel7_IRQn interrupt configuration */
        HAL_NVIC_SetPriority(DMA1_Channel7_IRQn, 6, 0);
        HAL_NVIC_EnableIRQ(DMA1_Channel7_IRQn);

        HAL_NVIC_SetPriority(USART2_IRQn, 10, 0);
        HAL_NVIC_EnableIRQ(USART2_IRQn);

        uInst2 = &self->inst;
        // udRxIT(self);
        udRxDMA(self);
        break;
    }

    default:
        break;
    }
}

void udDefConf(usartDrv_t *self)
{
    self->txTimeout = HAL_MAX_DELAY;
    self->rxTimeout = HAL_MAX_DELAY;
    self->rxSize = 1;
    self->txSize = 1;
}

uint8_t udRxIT(usartDrv_t *self)
{
    switch (self->inst)
    {
    case DRV_USART1:
    {
        return HAL_UART_Receive_IT(&huart1, self->rxBuff, self->rxSize);
        break;
    }

    case DRV_USART2:
    {
        return HAL_UART_Receive_IT(&huart2, self->rxBuff, self->rxSize);
        break;
    }

    default:
        break;
    }
    return HAL_ERROR;
}

uint8_t udRxBlck(usartDrv_t *self)
{
    switch (self->inst)
    {
    case DRV_USART1:
    {
        return HAL_UART_Receive(&huart1, self->rxBuff, self->rxSize, self->rxTimeout);
        break;
    }

    case DRV_USART2:
    {
        return HAL_UART_Receive(&huart2, self->rxBuff, self->rxSize, self->rxTimeout);
        break;
    }

    default:
        break;
    }
    return HAL_ERROR;
}

uint8_t udRxDMA(usartDrv_t *self)
{
    switch (self->inst)
    {
    case DRV_USART1:
    {
        return HAL_UART_Receive_DMA(&huart1, self->rxBuff, self->rxSize);
        break;
    }

    case DRV_USART2:
    {
        return HAL_UART_Receive_DMA(&huart2, self->rxBuff, self->rxSize);
        break;
    }

    default:
        break;
    }
    return HAL_ERROR;
}

uint8_t udTxIT(usartDrv_t *self)
{
    switch (self->inst)
    {
    case DRV_USART1:
    {
        return HAL_UART_Transmit_IT(&huart1, self->txBuff, self->txSize);
        break;
    }

    case DRV_USART2:
    {
        return HAL_UART_Receive_IT(&huart2, self->txBuff, self->txSize);
        break;
    }

    default:
        break;
    }
    return HAL_ERROR;
}

uint8_t udTxBlck(usartDrv_t *self)
{
    switch (self->inst)
    {
    case DRV_USART1:
    {
        return HAL_UART_Transmit(&huart1, self->txBuff, self->txSize, self->txTimeout);
        break;
    }

    case DRV_USART2:
    {
        return HAL_UART_Transmit(&huart2, self->txBuff, self->txSize, self->txTimeout);
        break;
    }

    default:
        break;
    }
    return HAL_ERROR;
}

uint8_t udTxDMA(usartDrv_t *self)
{
    switch (self->inst)
    {
    case DRV_USART1:
    {
        return HAL_UART_Transmit_DMA(&huart1, self->txBuff, self->txSize);
        break;
    }

    case DRV_USART2:
    {
        return HAL_UART_Transmit_DMA(&huart2, self->txBuff, self->txSize);
        break;
    }

    default:
        break;
    }
    return HAL_ERROR;
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(huart);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(huart);
    usartDrv_t *uart;
    if (huart->Instance == USART1)
    {
        uart = CONTAINER_OF(uInst1, usartDrv_t, inst);
        for (uint8_t idx = 0; idx < uart->rxSize; idx++)
            enqueue(&uart->rxQueue, uart->rxBuff[idx]);
    }
    else if (huart->Instance == USART2)
    {
        uart = CONTAINER_OF(uInst2, usartDrv_t, inst);
        for (uint8_t idx = 0; idx < uart->rxSize; idx++)
            enqueue(&uart->rxQueue, uart->rxBuff[idx]);
    }
    udRxDMA(uart);
    // udRxIT(uart);
}
