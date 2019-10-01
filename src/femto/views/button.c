#include "femto/views/button.h"

#include "femto/frame_data.h"

#include <stdbool.h>

// Internal button methods
void _Button_Update(FEMTO_View* view, FEMTO_FrameData* frameData);
void _Button_Render(FEMTO_View* view);
void _Button_Destroy(FEMTO_View* view);

FEMTO_View* FEMTO_CreateButton(char* name, FEMTO_View* parent, SDL_Renderer* renderer, FEMTO_TextRenderer* textRenderer, char* text, SDL_Rect rect)
{
    FEMTO_Button_Data* button = (FEMTO_Button_Data*) malloc(sizeof(struct FEMTO_Button_Data_int));

    button->renderer = renderer;
    button->text = text;
    button->rect = rect;
    button->textRenderer = textRenderer;
    button->state = UP;
    button->onClick = NULL;

    FEMTO_View* view = FEMTO_CreateView(name, button, parent, _Button_Update, _Button_Render, _Button_Destroy);

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

    FEMTO_FrameData_Mouse mouse = FEMTO_GetFrameDataMouseStatus(frameData);

    // Is mouse inside button?
    bool insideMouse = (mouse.x > button->rect.x) &&
                       (mouse.x < button->rect.x + button->rect.w) &&
                       (mouse.y > button->rect.y) &&
                       (mouse.y < button->rect.y + button->rect.h);

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

    SDL_SetRenderDrawColor(button->renderer,
        0,  // r
        0,  // g
        0,  // b
        255 // a
    );

    SDL_Rect textDim = FEMTO_GetRenderTextDim(button->textRenderer, button->text);
    textDim = (SDL_Rect) {
        button->rect.x + (button->rect.w/2) - (textDim.w/2),
        button->rect.y + (button->rect.h/2) - (textDim.h/2),
        textDim.w,
        textDim.h
    };

    switch(button->state)
    {
        case UP:
            SDL_RenderDrawRect(button->renderer, &button->rect);
            FEMTO_SetTextRendererColor(button->textRenderer, 0, 0, 0);
            break;
        case DOWN:
            SDL_RenderFillRect(button->renderer, &button->rect);
            FEMTO_SetTextRendererColor(button->textRenderer, 255, 255, 255);
            break;
    }

    FEMTO_RenderText(button->textRenderer, button->text, &textDim);
}

void _Button_Destroy(FEMTO_View* view)
{
    // Clear allocated variables
}