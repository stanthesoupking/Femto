#pragma once

#include "femto/application.h"

typedef struct FEMTO_System_int
{
    FEMTO_Application* runningApplication;
}
FEMTO_System;

FEMTO_System* FEMTO_CreateSystem();
void FEMTO_DestroySystem(FEMTO_System* system);

int FEMTO_StartSystem(FEMTO_System* system);