#pragma once

#include "femto/text_renderer.h"

typedef struct FEMTO_Application_int FEMTO_Application;

typedef struct FEMTO_System_int
{
    FEMTO_Application* runningApplication;
    FEMTO_TextRenderer* textRenderer;

    SDL_Window* window;
    SDL_Surface* screenSurface;
    SDL_Renderer* renderer;

    SDL_Rect applicationArea;
}
FEMTO_System;

FEMTO_System* FEMTO_CreateSystem();
void FEMTO_DestroySystem(FEMTO_System* system);

int FEMTO_StartSystem(FEMTO_System* system);