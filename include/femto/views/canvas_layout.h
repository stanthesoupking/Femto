#pragma once

#include <SDL.h>
#include <stdbool.h>

#include "femto/view.h"
#include "femto/colour.h"

typedef struct FEMTO_CanvasLayout_Data_int
{
    SDL_Renderer* renderer;
    SDL_Rect rect;

    FEMTO_Colour fillColour;
    bool fill;
}
FEMTO_CanvasLayout_Data;

FEMTO_View* FEMTO_CreateCanvasLayout(char* name, FEMTO_View* parent, SDL_Renderer* renderer, SDL_Rect rect);

void FEMTO_SetCanvasLayoutFillColour(FEMTO_View* view, FEMTO_Colour fillColour);
void FEMTO_SetCanvasLayoutFill(FEMTO_View* view, bool fill);