/**
 * @file spiDrv.c
 * @author Luis Maciel (luishenrique.8804@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-07-06
 *
 * @copyright Copyright (c) 2024
 *
 */

/* Includes ------------------------------------------------------------------*/
#include "spiDrv.h"
#include <stdlib.h>
#include "stm32f3xx_hal.h"
#include "stm32f303x8.h"
#include <string.h>

/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define SPI1_MOSI GPIO_PIN_5
#define SPI1_MISO GPIO_PIN_4
#define SPI1_CLK GPIO_PIN_3
#define SPI1_NSS1 GPIO_PIN_1
#define SPI1_PORT GPIOB

/* Private macro -------------------------------------------------------------*/
// declaração da macro OFFSETOF
#define OFFSETOF(TYPE, MEMBER) ((size_t) & ((TYPE *)0)->MEMBER)

// declaração da macro CONTAINER_OF
#define CONTAINER_OF(ptr, type, member) ({            \
 const __typeof( ((type *)0)->member ) *__mptr = (ptr);    \
 (type *)( (char *)__mptr - OFFSETOF(type,member) ); })

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;
sInst *sInst1;
/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

void sdInit(spiDrv_t *self, sInst instance)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    memset(self, 0, sizeof(spiDrv_t));
    initQueue(&self->rxQueue);
    self->inst = instance;
    sdDefConf(self);

    switch (instance)
    {
    case DRV_SPI1:
    {
        __HAL_RCC_SPI1_CLK_ENABLE();
        __HAL_RCC_GPIOB_CLK_ENABLE();

        HAL_GPIO_WritePin(SPI1_PORT, SPI1_NSS1, GPIO_PIN_SET);

        GPIO_InitStruct.Pin = SPI1_CLK | SPI1_MISO | SPI1_MOSI;
        GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
        HAL_GPIO_Init(SPI1_PORT, &GPIO_InitStruct);

        GPIO_InitStruct.Pin = SPI1_NSS1;
        GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
        GPIO_InitStruct.Pull = GPIO_NOPULL;
        GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
        HAL_GPIO_Init(SPI1_PORT, &GPIO_InitStruct);

        hspi1.Instance = SPI1;
        hspi1.Init.Mode = SPI_MODE_MASTER;
        hspi1.Init.Direction = SPI_DIRECTION_2LINES;
        hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
        hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
        hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
        hspi1.Init.NSS = SPI_NSS_SOFT;
        hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
        hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
        hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
        hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
        hspi1.Init.CRCPolynomial = 7;
        hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
        hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
        if (HAL_SPI_Init(&hspi1) != HAL_OK)
        {
            Error_Handler();
        }

        /* SPI1 interrupt Init */
        HAL_NVIC_SetPriority(SPI1_IRQn, 6, 0);
        HAL_NVIC_EnableIRQ(SPI1_IRQn);
        sInst1 = &self->inst;
        break;
    }

    default:
        break;
    }
}

void sdDefConf(spiDrv_t *self)
{
    self->txTimeout = 100;
    self->rxTimeout = 100;
    self->rxSize = 3;
    self->txSize = 3;
}

uint8_t sdInOutBlck(spiDrv_t *self)
{
    switch (self->inst)
    {
    case DRV_SPI1:
    {
        HAL_SPIEx_FlushRxFifo(&hspi1);
        return HAL_SPI_TransmitReceive(&hspi1, self->txBuff, self->rxBuff, self->rxSize, self->rxTimeout);
        break;
    }

    default:
        break;
    }
}

uint8_t sdInOutIT(spiDrv_t *self)
{
    switch (self->inst)
    {
    case DRV_SPI1:
    {
        HAL_SPIEx_FlushRxFifo(&hspi1);
        return HAL_SPI_TransmitReceive_IT(&hspi1, self->txBuff, self->rxBuff, self->rxSize);
        break;
    }

    default:
        break;
    }
}

uint8_t sdInBlck(spiDrv_t *self)
{
    switch (self->inst)
    {
    case DRV_SPI1:
    {
        return HAL_SPI_Receive(&hspi1, self->rxBuff, self->rxSize, self->rxTimeout);
        break;
    }

    default:
        break;
    }
}

uint8_t sdInIT(spiDrv_t *self)
{
    switch (self->inst)
    {
    case DRV_SPI1:
    {
        return HAL_SPI_Receive_IT(&hspi1, self->rxBuff, self->rxSize);
        break;
    }

    default:
        break;
    }
}

uint8_t sdOutBlck(spiDrv_t *self)
{
    switch (self->inst)
    {
    case DRV_SPI1:
    {
        return HAL_SPI_Transmit(&hspi1, self->txBuff, self->txSize, self->txTimeout);
        break;
    }

    default:
        break;
    }
}

uint8_t sdOutIT(spiDrv_t *self)
{
    switch (self->inst)
    {
    case DRV_SPI1:
    {
        return HAL_SPI_Transmit_IT(&hspi1, self->txBuff, self->txSize);
        break;
    }

    default:
        break;
    }
}

uint8_t sdNss(sNss_t slave)
{
    switch (slave)
    {

    case SLAVE1_SET:
    {
        HAL_GPIO_WritePin(SPI1_PORT, SPI1_NSS1, GPIO_PIN_SET);
        break;
    }

    case SLAVE1_RESET:
    {
        HAL_GPIO_WritePin(SPI1_PORT, SPI1_NSS1, GPIO_PIN_RESET);
        break;
    }

    default:
        break;
    }
}

/**
 * @brief  Tx Transfer completed callback.
 * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
 *               the configuration information for SPI module.
 * @retval None
 */
void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hspi);
}

/**
 * @brief  Rx Transfer completed callback.
 * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
 *               the configuration information for SPI module.
 * @retval None
 */
void HAL_SPI_RxCpltCallback(SPI_HandleTypeDef *hspi)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hspi);
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hspi);
    spiDrv_t *spi;
    if (hspi->Instance == SPI1)
    {
        spi = CONTAINER_OF(sInst1, spiDrv_t, inst);
        for (uint8_t idx = 0; idx < spi->rxSize; idx++)
            enqueue(&spi->rxQueue, spi->rxBuff[idx]);
    }
    sdInIT(spi);
}

/**
 * @brief  Tx and Rx Transfer completed callback.
 * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
 *               the configuration information for SPI module.
 * @retval None
 */
void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
    /* Prevent unused argument(s) compilation warning */
    UNUSED(hspi);
}
