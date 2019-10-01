#pragma once

#include <SDL.h>

#include "femto/system.h"
#include "femto/screen.h"
#include "femto/frame_data.h"

typedef struct FEMTO_Application_int FEMTO_Application;

struct FEMTO_Application_int
{
    FEMTO_System* system; // The system that owns this application

    char* name; // The name of the application
    void* applicationData; // Application-specific data

    FEMTO_Screen** screens; // UI Screens available to the application
    int activeScreen; // Index of the current active-screen
    
    // Update function, called each frame
    void (*update)(FEMTO_Application* application, FEMTO_FrameData* frameData);

    // Function called when the application is being destroyed,
    // used to free any variables allocated within applicationData
    void (*destroy)(FEMTO_Application* application);
};

FEMTO_Application* FEMTO_CreateApplication(FEMTO_System* system, char* name, void * data,
    FEMTO_Screen** screens, int activeScreen,
    void (*update)(FEMTO_Application* application, FEMTO_FrameData* frameData),
    void (*destroy)(FEMTO_Application* application)
);

void FEMTO_UpdateApplication(FEMTO_Application* application, FEMTO_FrameData* frameData);
void FEMTO_RenderApplication(FEMTO_Application* application);
void FEMTO_DestroyApplication(FEMTO_Application* application);