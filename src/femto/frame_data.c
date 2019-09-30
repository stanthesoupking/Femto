#include "femto/frame_data.h"

#include <stdio.h>
#include <stdlib.h>

struct FEMTO_FrameData_int
{
    bool final; // Has the frame data been finalised; can no longer be modified
    float dt; // Delta time in ms

    FEMTO_FrameData_Mouse mouse;
};

FEMTO_FrameData* FEMTO_CreateFrameData(float dt, int mouseX, int mouseY, bool mouseDown)
{
    FEMTO_FrameData* frameData = (FEMTO_FrameData*) malloc(sizeof(struct FEMTO_FrameData_int));

    frameData->final = false;
    frameData->dt = dt;
    frameData->mouse.x = mouseX;
    frameData->mouse.y = mouseY;
    frameData->mouse.down = mouseDown;

    return frameData;
}

void FEMTO_DestroyFrameData(FEMTO_FrameData* frameData)
{
    free(frameData);
}

void FEMTO_FinaliseFrameData(FEMTO_FrameData* frameData)
{
    frameData->final = true;
}

void FEMTO_SetFrameDataMousePosition(FEMTO_FrameData* frameData, int mouseX, int mouseY)
{
    if(!frameData->final)
    {
        frameData->mouse.x = mouseX;
        frameData->mouse.y = mouseY;
    }
    else
    {
        fprintf(stderr, "Warning: Program attempted setting mouse position in finalised frame data.\n");
    }
}

void FEMTO_SetFrameDataMouseDown(FEMTO_FrameData* frameData, bool mouseDown)
{
    if(!frameData->final)
    {
        frameData->mouse.down = mouseDown;
    }
    else
    {
        fprintf(stderr, "Warning: Program attempted setting mouse button state in finalised frame data.\n");
    }
}

FEMTO_FrameData_Mouse FEMTO_GetFrameDataMouseStatus(FEMTO_FrameData* frameData)
{
    return frameData->mouse;
}