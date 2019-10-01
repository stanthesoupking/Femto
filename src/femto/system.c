#include "femto/system.h"

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "femto/text_renderer.h"
#include "femto/views/button.h"

#include "applications/test/test_application.h"
#include "applications/hidden/bar.h"

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

// The height of the main panel
#define PANEL_HEIGHT 26

FEMTO_System* FEMTO_CreateSystem()
{
    FEMTO_System* system = (FEMTO_System*) malloc(sizeof(struct FEMTO_System_int));

    system->runningApplication = NULL;
    system->window = NULL;
    system->screenSurface = NULL;
    system->renderer = NULL;
    system->applicationArea = (SDL_Rect) {0, PANEL_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT - PANEL_HEIGHT};

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
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        fprintf(stderr, "Could not initialize SDL2: %s\n", SDL_GetError());
        return 1;
    }

    system->window = SDL_CreateWindow(
        FEMTO_STR_FULL_TITLE,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (system->window == NULL)
    {
        fprintf(stderr, "Could not create SDL2 window: %s\n", SDL_GetError());
        return 1;
    }

    IMG_Init(IMG_INIT_PNG);

    system->renderer = SDL_CreateRenderer(system->window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);

    #if FEMTO_2X_SCALE
        SDL_RenderSetScale(renderer, 2.0f, 2.0f);
    #endif

    // Create text renderer
    system->textRenderer = FEMTO_CreateTextRenderer(system->renderer, "../res/font.png", 7, 11);
    if(!system->textRenderer)
    {
        fprintf(stderr, "Could not create text renderer.\n");
        return 1;
    }

    SDL_Rect dst;
    dst.x = 16;
    dst.y = 16;
    dst.w = 100;
    dst.h = 100;

    FEMTO_Application* bar = APP_SpawnBar(system);

    // Start test application
    system->runningApplication = APP_SpawnTestApplication(system);

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
        FEMTO_FrameData* frameData = FEMTO_CreateFrameData(system, dt, mouseX, mouseY, mouseDown);
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

        // Update bar
        FEMTO_UpdateApplication(bar, frameData);

        // Update runnning application
        if(system->runningApplication != NULL)
        {
            FEMTO_UpdateApplication(system->runningApplication, frameData);
        }

        // Update cleanup
        FEMTO_DestroyFrameData(frameData);

        // Render elements

        // Clear white
        SDL_SetRenderDrawColor(system->renderer, 255, 255, 255, 255);
        SDL_RenderClear(system->renderer);

        // Render running application
        if(system->runningApplication != NULL)
        {
            FEMTO_RenderApplication(system->runningApplication);
        }

        // Render bar on top
        FEMTO_RenderApplication(bar);

        #if SHOW_FPS
        {
            float fps = 1.0f / dt;

            // Show FPS above everything else
            char fpsString[30];
            sprintf(fpsString, "FPS: %.f", fps);
            SDL_Rect fpsDim = FEMTO_GetRenderTextDim(system->textRenderer, fpsString);
            SDL_SetRenderDrawColor(system->renderer, 0, 0, 0, 255);
            SDL_RenderFillRect(system->renderer, &fpsDim);
            FEMTO_SetTextRendererColor(system->textRenderer, 255, 255, 0);
            FEMTO_RenderText(system->textRenderer, fpsString, &fpsDim);
        }
        #endif

        SDL_RenderPresent(system->renderer);
    }

    SDL_DestroyWindow(system->window);
    SDL_Quit();

    return 0;
}

void _sayHello(FEMTO_View* view)
{
    FEMTO_Button_Data* button = (FEMTO_Button_Data*) view->viewData;
    button->text = "You clicked me!";
    printf("Hello!\n");
}