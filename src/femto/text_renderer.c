#include "femto/text_renderer.h"

#include <SDL_image.h>
#include <stdlib.h>
#include <string.h>

struct FEMTO_TextRenderer_int
{
    SDL_Texture* src;
    SDL_Renderer* renderer;
    int charWidth;
    int charHeight;
};

FEMTO_TextRenderer* FEMTO_CreateTextRenderer(SDL_Renderer* renderer, char* src, int charWidth, int charHeight)
{
    FEMTO_TextRenderer* textRenderer = (FEMTO_TextRenderer*) malloc(sizeof(struct FEMTO_TextRenderer_int));

    textRenderer->renderer = renderer;
    textRenderer->charWidth = charWidth;
    textRenderer->charHeight = charHeight;
    
    IMG_Init(IMG_INIT_PNG);

    SDL_Texture* srcTexture = IMG_LoadTexture(renderer, src);

    if(!srcTexture)
    {
        // Failed loading source texture
        free(srcTexture);
        free(textRenderer);
        return NULL;
    }

    textRenderer->src = srcTexture;

    return textRenderer;
}

void FEMTO_DestroyTextRenderer(FEMTO_TextRenderer* textRenderer)
{
    free(textRenderer->src);
    free(textRenderer);
}

void FEMTO_SetTextRendererColor(FEMTO_TextRenderer* textRenderer, float r, float g, float b)
{
    SDL_SetTextureColorMod(textRenderer->src, r, g, b);
}

void FEMTO_RenderText(FEMTO_TextRenderer* textRenderer, char* text, SDL_Rect* dst)
{
    int textLength = strlen(text);

    SDL_Rect src;
    src.w = textRenderer->charWidth;
    src.h = textRenderer->charHeight;

    SDL_Rect idst;
    idst.w = textRenderer->charWidth;
    idst.h = textRenderer->charHeight;

    int i = 0;
    char c;
    for(int i = 0; i < textLength; i++)
    {
        c = text[i];
        
        // Is the character renderable?
        if((c < ' ') || (c > '~'))
        {
            continue;
        }

        int cx = ((int) c - 32) % 18;
        int cy = ((int) c - 32) / 18;

        src.x = cx * src.w;
        src.y = cy * src.h;

        idst.x = idst.w * i  + dst->x;
        idst.y = dst->y;

        SDL_RenderCopy(textRenderer->renderer, textRenderer->src, &src, &idst);
    }
}

SDL_Rect FEMTO_GetRenderTextDim(FEMTO_TextRenderer* textRenderer, char* text)
{
    return (SDL_Rect)
    {
        0,
        0,
        textRenderer->charWidth * strlen(text),
        textRenderer->charHeight
    };
}