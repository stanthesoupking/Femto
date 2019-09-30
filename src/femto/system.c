#include "femto/system.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "femto/text_renderer.h"
#include "femto/button.h"

#define FEMTO_STR_TITLE "Femto"
#define FEMTO_STR_VERSION "0.0.1"
#define FEMTO_STR_FULL_TITLE FEMTO_STR_TITLE " v" FEMTO_STR_VERSION

// Should the renderer upscale by 2x?
#define FEMTO_2X_SCALE false

// Should the current FPS be displayed in the top-left corner of the screen?
#define SHOW_FPS true

// Dimensions of the screen
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480

FEMTO_System* FEMTO_CreateSystem()
{
    FEMTO_System* system = (FEMTO_System*) malloc(sizeof(struct FEMTO_System_int));

    system->runningApplication = NULL;

    return system;
}

void FEMTO_DestroySystem(FEMTO_System* system)
{
    free(system);
}

// Test function
void _sayHello(FEMTO_View* view);

int FEMTO_StartSystem(FEMTO_System* system)
{
    SDL_Window *window = NULL;
    SDL_Surface *screenSurface = NULL;
    SDL_Renderer *renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "Could not initialize SDL2: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(
        FEMTO_STR_FULL_TITLE,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        fprintf(stderr, "Could not create SDL2 window: %s\n", SDL_GetError());
        return 1;
    }

    IMG_Init(IMG_INIT_PNG);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    #if FEMTO_2X_SCALE
        SDL_RenderSetScale(renderer, 2.0f, 2.0f);
    #endif

    // Create text renderer
    FEMTO_TextRenderer* textRenderer = FEMTO_CreateTextRenderer(renderer, "../res/font.png", 7, 11);
    if(!textRenderer)
    {
        fprintf(stderr, "Could not create text renderer.\n");
        return 1;
    }

    SDL_Rect dst;
    dst.x = 16;
    dst.y = 16;
    dst.w = 100;
    dst.h = 100;

    FEMTO_View* button = FEMTO_CreateButton("MyButton", textRenderer, renderer, "Hello Button :)", (SDL_Rect) {16, 64, 120, 32});
    FEMTO_SetButtonOnClick(button, _sayHello);

    int mouseX = 0;
    int mouseY = 0;
    bool mouseDown = false;

    Uint32 pTime = SDL_GetTicks();

    SDL_Event e;
    bool quit = false;
    while (!quit){
        // Calculate delta time
        Uint32 nTime = SDL_GetTicks();
        float dt = (nTime - pTime) / 1000.0f;
        pTime = nTime;

        // Create new frame data
        FEMTO_FrameData* frameData = FEMTO_CreateFrameData(dt, mouseX, mouseY, mouseDown);
        while (SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
            else if (e.type == SDL_MOUSEMOTION)
            {
                SDL_MouseMotionEvent m = (SDL_MouseMotionEvent) e.motion;
                mouseX = m.x;
                mouseY = m.y;
                mouseDown = m.state & SDL_BUTTON_LMASK;
                FEMTO_SetFrameDataMousePosition(frameData, mouseX, mouseY);
                FEMTO_SetFrameDataMouseDown(frameData, mouseDown);
            }
            else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
            {
                SDL_MouseButtonEvent m = (SDL_MouseButtonEvent) e.button;
                mouseX = m.x;
                mouseY = m.y;
                mouseDown = m.state & SDL_PRESSED;
                FEMTO_SetFrameDataMousePosition(frameData, mouseX, mouseY);
                FEMTO_SetFrameDataMouseDown(frameData, mouseDown);
            }
        }
        FEMTO_FinaliseFrameData(frameData);

        // Update elements
        FEMTO_UpdateView(button, frameData);

        // Update cleanup
        FEMTO_DestroyFrameData(frameData);

        // Render elements

        // Clear white
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        FEMTO_SetTextRendererColor(textRenderer, 0, 0, 0);
        FEMTO_RenderText(textRenderer, FEMTO_STR_FULL_TITLE, &dst);
        FEMTO_RenderView(button);

        #if SHOW_FPS
        {
            float fps = 1.0f / dt;

            // Show FPS above everything else
            FEMTO_SetTextRendererColor(textRenderer, 255, 255, 0);
            char fpsString[30];
            sprintf(fpsString, "FPS: %.f", fps);
            SDL_Rect fpsDim = FEMTO_GetRenderTextDim(textRenderer, fpsString);
            SDL_RenderFillRect(renderer, &fpsDim);
            FEMTO_RenderText(textRenderer, fpsString, &fpsDim);
        }
        #endif

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}

void _sayHello(FEMTO_View* view)
{
    FEMTO_Button_Data* button = (FEMTO_Button_Data*) view->viewData;
    button->text = "You clicked me!";
    printf("Hello!\n");
}