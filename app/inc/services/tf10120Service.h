/**
 * @file tf1020Service.h
 * @author luis (luis@logpyx.com)
 * @brief Laser Distance Sensor
 * @version 0.1
 * @date 2024-06-29
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "stdint.h"

typedef enum
{
    sPOS_DEV=1,
    sNEG_DEV,
    sRATE,
    sMODE,
    sMAX_DIST,
    sMETHOD,
    sID,
    sCALIB
} setCommands_t;

typedef enum
{
    rDEVIATION=1,
    rRATE,
    rMODE,
    rMAX_DIST,
    rMETHOD,
    rDIST,
    rID,
    rCALIB
} readCommands_t;

void tfsInit(void);
void tfsSet(setCommands_t cmd, uint16_t data);
uint16_t tfsRead(readCommands_t cmd);
uint16_t tfsGetDist(void);