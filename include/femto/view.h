#pragma once

#include <SDL.h>

#include "femto/frame_data.h"
#include "femto/linked_list.h"

typedef struct FEMTO_View_int FEMTO_View;

struct FEMTO_View_int
{
    // The name of the view for identification purposes
    char* name;

    // Data storage for view-specific properties
    void* viewData;

    // The application that owns this view
    FEMTO_Application* application;

    // The parent of this view
    FEMTO_View* parent;

    // The children contained inside this view
    FEMTO_LinkedList* children;

    // The view rect as set by the parent of the view
    SDL_Rect rect;
    
    // If the absolute rect is not null then it will override the 'rect' property
    SDL_Rect* absoluteRect;

    // Called once per frame, before render
    void (*update)(FEMTO_View* view, FEMTO_FrameData* frameData);

    // Called once per frame to render the view to the screen
    void (*render)(FEMTO_View* view);

    // Called on destruction of the view, should be used to safely free any allocated
    // variables from within te view's 'viewData' property.
    void (*destroy)(FEMTO_View* view);
};

FEMTO_View* FEMTO_CreateView(char* name, void* viewData,
    FEMTO_Application* application, FEMTO_View* parent,
    void (*update)(FEMTO_View* view, FEMTO_FrameData* frameData),
    void (*render)(FEMTO_View* view),
    void (*destroy)(FEMTO_View* view)
);

void FEMTO_AddChildView(FEMTO_View* view, FEMTO_View* child);
void FEMTO_UpdateView(FEMTO_View* view, FEMTO_FrameData* frameData);
void FEMTO_RenderView(FEMTO_View* view);
void FEMTO_DestroyView(FEMTO_View* view);
void FEMTO_SetViewRect(FEMTO_View* view, SDL_Rect rect);
void FEMTO_ClearViewAbsoluteRect(FEMTO_View* view);
void FEMTO_SetViewAbsoluteRect(FEMTO_View* view, SDL_Rect absoluteRect);
SDL_Rect FEMTO_GetViewRect(FEMTO_View* view);
SDL_Renderer* FEMTO_GetViewRenderer(FEMTO_View* view);