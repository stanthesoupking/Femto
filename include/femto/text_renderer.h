#pragma once

#include <SDL.h>

typedef struct FEMTO_TextRenderer_int FEMTO_TextRenderer;

FEMTO_TextRenderer* FEMTO_CreateTextRenderer(SDL_Renderer* renderer, char* src, int charWidth, int charHeight);
void FEMTO_DestroyTextRenderer(FEMTO_TextRenderer* textRenderer);

void FEMTO_SetTextRendererColor(FEMTO_TextRenderer* textRenderer, float r, float g, float b);
void FEMTO_RenderText(FEMTO_TextRenderer* textRenderer, char* text, SDL_Rect* dst);
SDL_Rect FEMTO_GetRenderTextDim(FEMTO_TextRenderer* textRenderer, char* text);