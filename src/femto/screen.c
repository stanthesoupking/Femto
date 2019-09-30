#include "femto/screen.h"

#include <stdlib.h>

FEMTO_Screen* FEMTO_CreateScreen(FEMTO_View* root)
{
    FEMTO_Screen* screen = (FEMTO_Screen*) malloc(sizeof(struct FEMTO_Screen_int));

    screen->root = root;

    return screen;
}

void FEMTO_DestroyScreen(FEMTO_Screen* screen)
{
    // Free the screen's root element
    FEMTO_DestroyView(screen->root);

    free(screen);
}

void FEMTO_RenderScreen(FEMTO_Screen* screen)
{
    FEMTO_RenderView(screen->root);
}