#pragma once

#include <SDL.h>

#include "femto/view.h"
#include "femto/text_renderer.h"

typedef struct FEMTO_Label_Data_int
{
    FEMTO_TextRenderer* textRenderer;
    char* text;
}
FEMTO_Label_Data;

FEMTO_View* FEMTO_CreateLabel(char* name, FEMTO_Application* application, FEMTO_View* parent, FEMTO_TextRenderer* textRenderer, char* text);