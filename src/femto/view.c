#include "femto/view.h"

#include "femto/application.h"

#include <stdlib.h>
#include <stdarg.h>

FEMTO_View* FEMTO_CreateView(char* name, void* viewData,
    FEMTO_Application* application, FEMTO_View* parent,
    void (*update)(FEMTO_View* view, FEMTO_FrameData* frameData),
    void (*render)(FEMTO_View* view),
    void (*destroy)(FEMTO_View* view)
)
{
    FEMTO_View* view = (FEMTO_View*) malloc(sizeof(struct FEMTO_View_int));

    view->application = application;

    view->parent = parent;
    if(parent != NULL)
    {
        FEMTO_AddChildView(parent, view);
    }

    view->children = FEMTO_CreateLinkedList();

    view->name = name;
    view->viewData = viewData;
    view->update = update;
    view->render = render;
    view->destroy = destroy;
    view->rect = (SDL_Rect) {0, 0, 0, 0};
    view->absoluteRect = NULL;

    return view;
}

void FEMTO_AddChildView(FEMTO_View* view, FEMTO_View* child)
{
    FEMTO_LinkedListInsert(view->children, child);
    child->parent = view;
}

// Method to be passed to FEMTO_LinkedListTraverse for updating children
void _View_UpdateChild(void* data, void* extra)
{
    FEMTO_View* view = (FEMTO_View*) data;
    FEMTO_FrameData* frameData = (FEMTO_FrameData*) extra;

    FEMTO_UpdateView(view, frameData);
}

void FEMTO_UpdateView(FEMTO_View* view, FEMTO_FrameData* frameData)
{
    // Update self
    view->update(view, frameData);

    // Update children
    FEMTO_LinkedListTraverse(view->children, _View_UpdateChild, frameData);
}

// Method to be passed to FEMTO_LinkedListTraverse for rendering children
void _View_RenderChild(void* data, void* extra)
{
    FEMTO_View* view = (FEMTO_View*) data;
    FEMTO_RenderView(view);
}

void FEMTO_RenderView(FEMTO_View* view)
{
    // Render self
    view->render(view);

    // Render children
    FEMTO_LinkedListTraverse(view->children, _View_RenderChild, NULL);
}

void FEMTO_DestroyView(FEMTO_View* view)
{
    view->destroy(view);
    free(view);
}

void FEMTO_SetViewRect(FEMTO_View* view, SDL_Rect rect)
{
    view->rect = rect;
}

void FEMTO_SetViewAbsoluteRect(FEMTO_View* view, SDL_Rect absoluteRect)
{
    if(view->absoluteRect != NULL)
    {
        free(view->absoluteRect);
    }
    else
    {
        view->absoluteRect = (SDL_Rect*) malloc(sizeof(SDL_Rect));
        *(view->absoluteRect) = absoluteRect;
    }
}

void FEMTO_ClearViewAbsoluteRect(FEMTO_View* view)
{
    if(view->absoluteRect != NULL)
    {
        free(view->absoluteRect);
        view->absoluteRect = NULL;
    }
}

SDL_Rect FEMTO_GetViewRect(FEMTO_View* view)
{
    if(view->absoluteRect != NULL)
    {
        return *(view->absoluteRect);
    }
    else
    {
        return view->rect;
    }
}

SDL_Renderer* FEMTO_GetViewRenderer(FEMTO_View* view)
{
    return view->application->system->renderer;
}