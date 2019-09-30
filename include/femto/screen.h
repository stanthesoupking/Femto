#pragma once

#include "femto/view.h"

typedef struct FEMTO_Screen_int
{
    FEMTO_View* root;
}
FEMTO_Screen;

FEMTO_Screen* FEMTO_CreateScreen(FEMTO_View* root);
void FEMTO_DestroyScreen(FEMTO_Screen* screen);

void FEMTO_RenderScreen(FEMTO_Screen* screen);