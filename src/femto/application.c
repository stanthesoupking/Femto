#include "femto/application.h"

#include <stdlib.h>

FEMTO_Application* FEMTO_CreateApplication(FEMTO_System* system, char* name, void * data,
    FEMTO_Screen** screens, int activeScreen,
    void (*update)(FEMTO_Application* application, FEMTO_FrameData* frameData),
    void (*destroy)(FEMTO_Application* application)
)
{
    FEMTO_Application* application = (FEMTO_Application*) malloc(sizeof(struct FEMTO_Application_int));

    application->system = system;
    application->name = name;
    application->applicationData = data;
    application->screens = screens;
    application->activeScreen = activeScreen;
    application->update = update;
    application->destroy = destroy;
    application->rect = system->applicationArea;

    return application;
}

void FEMTO_DestroyApplication(FEMTO_Application* application)
{
    // Call the application's destroy method
    application->destroy(application);

    free(application->name);
    free(application->applicationData);
    
    // TODO: Free screens
    // ...

    free(application);
}

SDL_Rect FEMTO_GetApplicationRect(FEMTO_Application* application)
{
    return application->rect;
}

void FEMTO_UpdateApplication(FEMTO_Application* application, FEMTO_FrameData* frameData)
{
    application->update(application, frameData);

    // Get root view
    FEMTO_View* root = application->screens[application->activeScreen]->root;

    SDL_Rect viewRect = application->rect;
    viewRect.y = 0;
    viewRect.x = 0;

    // Update root view rect to fill application area
    FEMTO_SetViewRect(root, viewRect);

    // Update root view
    FEMTO_UpdateView(application->screens[application->activeScreen]->root, frameData);
}

void FEMTO_RenderApplication(FEMTO_Application* application)
{
    // Render application inside its rect
    SDL_RenderSetViewport(application->system->renderer,
                          &application->rect);

    // Render the active screen      
    FEMTO_RenderScreen(application->screens[application->activeScreen]);
}