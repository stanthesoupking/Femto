#include "femto/view.h"

#include <stdlib.h>

FEMTO_View* FEMTO_CreateView(char* name, void* viewData,
    void (*update)(FEMTO_View* view, FEMTO_FrameData* frameData),
    void (*render)(FEMTO_View* view),
    void (*destroy)(FEMTO_View* view)
)
{
    FEMTO_View* view = (FEMTO_View*) malloc(sizeof(struct FEMTO_View_int));

    view->name = name;
    view->viewData = viewData;
    view->update = update;
    view->render = render;
    view->destroy = destroy;

    return view;
}

void FEMTO_UpdateView(FEMTO_View* view, FEMTO_FrameData* frameData)
{
    view->update(view, frameData);

    // TODO: Update children
    // ...
}

void FEMTO_RenderView(FEMTO_View* view)
{
    view->render(view);

    // TODO: Render children
    // ...
}

void FEMTO_DestroyView(FEMTO_View* view)
{
    view->destroy(view);
    free(view);
}