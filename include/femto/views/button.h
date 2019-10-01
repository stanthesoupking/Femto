#pragma once

#include <SDL.h>

#include "femto/view.h"
#include "femto/text_renderer.h"

enum FEMTO_Button_State
{
    UP,
    DOWN
};

typedef struct FEMTO_Button_Data_int
{
    SDL_Renderer* renderer;
    FEMTO_TextRenderer* textRenderer;
    enum FEMTO_Button_State state;
    char* text;
    SDL_Rect rect;
    void (*onClick)(FEMTO_View* view);
}
FEMTO_Button_Data;

FEMTO_View* FEMTO_CreateButton(char* name, FEMTO_View* parent, SDL_Renderer* renderer, FEMTO_TextRenderer* textRenderer, char* text, SDL_Rect rect);
void FEMTO_SetButtonOnClick(FEMTO_View* view, void (*onClick)(FEMTO_View* view));