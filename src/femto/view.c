#include "femto/view.h"

#include <stdlib.h>
#include <stdarg.h>

FEMTO_View* FEMTO_CreateView(char* name, void* viewData, FEMTO_View* parent,
    void (*update)(FEMTO_View* view, FEMTO_FrameData* frameData),
    void (*render)(FEMTO_View* view),
    void (*destroy)(FEMTO_View* view)
)
{
    FEMTO_View* view = (FEMTO_View*) malloc(sizeof(struct FEMTO_View_int));

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