#include "femto/views/canvas_layout.h"

#include <stdlib.h>

// Internal canvas layout methods
void _CanvasLayout_Update(FEMTO_View* view, FEMTO_FrameData* frameData);
void _CanvasLayout_Render(FEMTO_View* view);
void _CanvasLayout_Destroy(FEMTO_View* view);

FEMTO_View* FEMTO_CreateCanvasLayout(char* name, FEMTO_View* parent, SDL_Renderer* renderer, SDL_Rect rect)
{
    FEMTO_CanvasLayout_Data* data = (FEMTO_CanvasLayout_Data*) malloc(sizeof(struct FEMTO_CanvasLayout_Data_int));
    data->renderer = renderer;
    data->rect = rect;

    FEMTO_View* view = FEMTO_CreateView(name, data, parent, _CanvasLayout_Update,
        _CanvasLayout_Render, _CanvasLayout_Destroy);

    return view;
}

void FEMTO_SetCanvasLayoutFillColour(FEMTO_View* view, FEMTO_Colour fillColour)
{
    FEMTO_CanvasLayout_Data* data = (FEMTO_CanvasLayout_Data*) view->viewData;
    
    data->fillColour = fillColour;
}

void FEMTO_SetCanvasLayoutFill(FEMTO_View* view, bool fill)
{
    FEMTO_CanvasLayout_Data* data = (FEMTO_CanvasLayout_Data*) view->viewData;
    
    data->fill = fill;
}

void _CanvasLayout_Update(FEMTO_View* view, FEMTO_FrameData* frameData)
{

}

void _CanvasLayout_Render(FEMTO_View* view)
{
    FEMTO_CanvasLayout_Data* data = (FEMTO_CanvasLayout_Data*) view->viewData;

    if(data->fill)
    {
        SDL_Renderer* renderer = data->renderer;
        FEMTO_SetRenderColour(renderer, &data->fillColour);
        SDL_RenderFillRect(renderer, &data->rect);
    }
}

void _CanvasLayout_Destroy(FEMTO_View* view)
{
    FEMTO_CanvasLayout_Data* data = (FEMTO_CanvasLayout_Data*) view->viewData;
    free(data);
}