#pragma once

#include <SDL.h>
#include <stdbool.h>

#include "femto/system.h"

typedef struct FEMTO_FrameData_int FEMTO_FrameData;

typedef struct FEMTO_FrameData_Mouse_int
{
    int x;
    int y;
    bool down;
}
FEMTO_FrameData_Mouse;

FEMTO_FrameData* FEMTO_CreateFrameData(FEMTO_System* system, float dt, int mouseX, int mouseY, bool mouseDown);
void FEMTO_DestroyFrameData(FEMTO_FrameData* frameData);

void FEMTO_FinaliseFrameData(FEMTO_FrameData* frameData);

void FEMTO_SetFrameDataMousePosition(FEMTO_FrameData* frameData, int mouseX, int mouseY);
void FEMTO_SetFrameDataMouseDown(FEMTO_FrameData* frameData, bool mouseDown);

FEMTO_FrameData_Mouse FEMTO_GetFrameDataMouseStatus(SDL_Rect* applicationArea, FEMTO_FrameData* frameData);