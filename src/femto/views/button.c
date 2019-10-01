#include "femto/views/button.h"

#include "femto/frame_data.h"
#include "femto/application.h"

#include <stdbool.h>

// Internal button methods
void _Button_Update(FEMTO_View* view, FEMTO_FrameData* frameData);
void _Button_Render(FEMTO_View* view);
void _Button_Destroy(FEMTO_View* view);

FEMTO_View* FEMTO_CreateButton(char* name, FEMTO_Application* application, FEMTO_View* parent, FEMTO_TextRenderer* textRenderer, char* text)
{
    FEMTO_Button_Data* button = (FEMTO_Button_Data*) malloc(sizeof(struct FEMTO_Button_Data_int));

    button->text = text;
    button->textRenderer = textRenderer;
    button->state = UP;
    button->onClick = NULL;

    FEMTO_View* view = FEMTO_CreateView(name, button, application, parent, _Button_Update, _Button_Render, _Button_Destroy);

    return view;
}

void FEMTO_SetButtonOnClick(FEMTO_View* view, void (*onClick)(FEMTO_View* view))
{
    FEMTO_Button_Data* button = (FEMTO_Button_Data*) view->viewData;
    button->onClick = onClick;
}

void _Button_Update(FEMTO_View* view, FEMTO_FrameData* frameData)
{
    FEMTO_Button_Data* button = (FEMTO_Button_Data*) view->viewData;
    SDL_Rect viewRect = FEMTO_GetViewRect(view);

    SDL_Rect applicationRect = FEMTO_GetApplicationRect(view->application);
    FEMTO_FrameData_Mouse mouse = FEMTO_GetFrameDataMouseStatus(&applicationRect, frameData);

    // Is mouse inside button?
    bool insideMouse = (mouse.x > viewRect.x) &&
                       (mouse.x < viewRect.x + viewRect.w) &&
                       (mouse.y > viewRect.y) &&
                       (mouse.y < viewRect.y + viewRect.h);

    // Is mouse down?
    if(mouse.down && insideMouse)
    {
        button->state = DOWN;
    }
    else if(!mouse.down && insideMouse && button->state == DOWN)
    {
        // Trigger on click
        if(button->onClick != NULL)
        {
            button->onClick(view);
        }
        button->state = UP;
    }
    else
    {
        button->state = UP;
    }
}

void _Button_Render(FEMTO_View* view)
{
    FEMTO_Button_Data* button = (FEMTO_Button_Data*) view->viewData;

    SDL_Renderer* renderer = FEMTO_GetViewRenderer(view);
    SDL_Rect viewRect = FEMTO_GetViewRect(view);

    SDL_SetRenderDrawColor(renderer,
        0,  // r
        0,  // g
        0,  // b
        255 // a
    );

    SDL_Rect textDim = FEMTO_GetRenderTextDim(button->textRenderer, button->text);
    textDim = (SDL_Rect) {
        viewRect.x + (viewRect.w/2) - (textDim.w/2),
        viewRect.y + (viewRect.h/2) - (textDim.h/2),
        textDim.w,
        textDim.h
    };

    switch(button->state)
    {
        case UP:
            SDL_RenderDrawRect(renderer, &viewRect);
            FEMTO_SetTextRendererColor(button->textRenderer, 0, 0, 0);
            break;
        case DOWN:
            SDL_RenderFillRect(renderer, &viewRect);
            FEMTO_SetTextRendererColor(button->textRenderer, 255, 255, 255);
            break;
    }

    FEMTO_RenderText(button->textRenderer, button->text, &textDim);
}

void _Button_Destroy(FEMTO_View* view)
{
    // Clear allocated variables
}