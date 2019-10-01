#pragma once

#include <SDL.h>

typedef struct FEMTO_Colour_int
{
    float r;
    float g;
    float b;
    float a;    
}
FEMTO_Colour;

FEMTO_Colour FEMTO_CreateColour(float r, float g, float b, float a);
void FEMTO_SetRenderColour(SDL_Renderer* renderer, FEMTO_Colour* colour);