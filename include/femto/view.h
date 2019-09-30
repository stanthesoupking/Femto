#pragma once

#include <SDL.h>

#include "femto/frame_data.h"

typedef struct FEMTO_View_int FEMTO_View;

struct FEMTO_View_int
{
    char* name;
    void* viewData;

    void (*update)(FEMTO_View* view, FEMTO_FrameData* frameData);
    void (*render)(FEMTO_View* view);
    void (*destroy)(FEMTO_View* view);
};

FEMTO_View* FEMTO_CreateView(char* name, void* viewData,
    void (*update)(FEMTO_View* view, FEMTO_FrameData* frameData),
    void (*render)(FEMTO_View* view),
    void (*destroy)(FEMTO_View* view)
);

void FEMTO_UpdateView(FEMTO_View* view, FEMTO_FrameData* frameData);
void FEMTO_RenderView(FEMTO_View* view);
void FEMTO_DestroyView(FEMTO_View* view);