#include "femto/views/label.h"

#include "femto/frame_data.h"
#include "femto/application.h"

#include <stdbool.h>

// Internal label methods
void _Label_Update(FEMTO_View* view, FEMTO_FrameData* frameData);
void _Label_Render(FEMTO_View* view);
void _Label_Destroy(FEMTO_View* view);

FEMTO_View* FEMTO_CreateLabel(char* name, FEMTO_Application* application, FEMTO_View* parent, FEMTO_TextRenderer* textRenderer, char* text)
{
    FEMTO_Label_Data* label = (FEMTO_Label_Data*) malloc(sizeof(struct FEMTO_Label_Data_int));

    label->text = text;
    label->textRenderer = textRenderer;

    FEMTO_View* view = FEMTO_CreateView(name, label, application, parent, _Label_Update, _Label_Render, _Label_Destroy);

    return view;
}

void _Label_Update(FEMTO_View* view, FEMTO_FrameData* frameData)
{
    // Do nothing
}

void _Label_Render(FEMTO_View* view)
{
    FEMTO_Label_Data* label = (FEMTO_Label_Data*) view->viewData;
    
    SDL_Renderer* renderer = FEMTO_GetViewRenderer(view);
    SDL_Rect viewRect = FEMTO_GetViewRect(view);

    SDL_Rect textDim = FEMTO_GetRenderTextDim(label->textRenderer, label->text);
    textDim = (SDL_Rect) {
        viewRect.x + (viewRect.w/2) - (textDim.w/2),
        viewRect.y + (viewRect.h/2) - (textDim.h/2),
        textDim.w,
        textDim.h
    };

    FEMTO_SetTextRendererColor(label->textRenderer, 0, 0, 0);
    FEMTO_RenderText(label->textRenderer, label->text, &textDim);
}

void _Label_Destroy(FEMTO_View* view)
{
    // Clear allocated variables
}