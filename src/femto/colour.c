#include "femto/colour.h"

FEMTO_Colour FEMTO_CreateColour(float r, float g, float b, float a)
{
    return (FEMTO_Colour) {r, g, b, a};
}

void FEMTO_SetRenderColour(SDL_Renderer* renderer, FEMTO_Colour* colour)
{
    SDL_SetRenderDrawColor(renderer,
        colour->r * 255,
        colour->g * 255,
        colour->b * 255,
        colour->a * 255
    );
}