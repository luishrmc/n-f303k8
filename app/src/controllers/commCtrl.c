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
/* Private includes ----------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
usartDrv_t u2;
/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

void commCtrlRun(void)
{
}

void commCtrlInit(void)
{
    udInit(&u2, DRV_USART2);
}
