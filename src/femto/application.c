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

void FEMTO_UpdateApplication(FEMTO_Application* application, FEMTO_FrameData* frameData)
{
    application->update(application, frameData);
}

void FEMTO_RenderApplication(FEMTO_Application* application)
{
    // Render the active screen
    FEMTO_RenderScreen(application->screens[application->activeScreen]);
}