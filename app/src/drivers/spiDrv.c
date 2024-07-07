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
#define SPI1_CLK GPIO_PIN_5
#define SPI1_MISO GPIO_PIN_6
#define SPI1_MOSI GPIO_PIN_7
#define SPI1_NSS1 GPIO_PIN_4
#define SPI1_PORT GPIOA

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;
/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

void sdInit(spiDrv_t *self, sInst instance)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    switch (instance)
    {
    case DRV_SPI1:
    {
        __HAL_RCC_SPI1_CLK_ENABLE();
        __HAL_RCC_GPIOA_CLK_ENABLE();

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
        hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
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
        break;
    }

    default:
        break;
    }
}

uint8_t sdInOut(spiDrv_t *self)
{
    switch (self->inst)
    {
    case DRV_SPI1:
    {
        HAL_SPIEx_FlushRxFifo(&hspi1);
        HAL_SPI_TransmitReceive(&hspi1, self->tx, self->rx, self->size, HAL_MAX_DELAY);
        break;
    }

    default:
        break;
    }
}

uint8_t sdIn(spiDrv_t *self, sInst *data)
{
    switch (self->inst)
    {
    case DRV_SPI1:
    {
        HAL_SPI_Transmit(&hspi1, self->tx, self->size, HAL_MAX_DELAY);
        break;
    }

    default:
        break;
    }
}

uint8_t sdOut(spiDrv_t *self)
{
    switch (self->inst)
    {
    case DRV_SPI1:
    {
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
