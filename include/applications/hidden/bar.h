#pragma once

#include "femto/application.h"

typedef struct APP_Bar_Data_int
{
    SDL_Renderer* renderer;
}
APP_Bar_Data;

FEMTO_Application* APP_SpawnBar(FEMTO_System* system);