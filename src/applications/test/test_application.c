#include "applications/test/test_application.h"

#include <stdlib.h>
#include "femto/views/label.h"
#include "femto/views/button.h"
#include "femto/views/canvas_layout.h"

// Internal bar methods
void _APP_TestApplication_Update(FEMTO_Application* application, FEMTO_FrameData* frameData);
void _APP_TestApplication_Destroy(FEMTO_Application* application);

FEMTO_Application* APP_SpawnTestApplication(FEMTO_System* system)
{
    APP_TestApplication_Data* data = (APP_TestApplication_Data*) malloc(sizeof(struct APP_TestApplication_Data_int));

    FEMTO_Screen** screens = (FEMTO_Screen**) malloc(sizeof(FEMTO_Screen*) * 1);

    FEMTO_Application* application = FEMTO_CreateApplication(system,
        "Test_Application", data, screens, 0, _APP_TestApplication_Update,
        _APP_TestApplication_Destroy);

    // Add canvas layout (root)
    FEMTO_View* root = FEMTO_CreateCanvasLayout("TestApplicationCanvas", application, NULL);
    FEMTO_SetCanvasLayoutFillColour(root, FEMTO_CreateColour(1.0f, 1.0f, 1.0f, 1.0f));
    FEMTO_SetCanvasLayoutFill(root, true);

    // Add welcome label
    FEMTO_View* welcomeLabel = FEMTO_CreateLabel("WelcomeLabel", application, root,
        system->textRenderer, "Welcome to the Femto test application!");
    
    FEMTO_SetViewAbsoluteRect(welcomeLabel, (SDL_Rect) {5, 5, 800, 32});

    // Add test button
    FEMTO_View* testButton = FEMTO_CreateButton("TestButton", application, root,
        system->textRenderer, "Hello World!");

    FEMTO_SetViewAbsoluteRect(testButton, (SDL_Rect) {5, 38, 790, 32});

    FEMTO_Screen* screen = FEMTO_CreateScreen(root);
    screens[0] = screen;

    return application;
}

void _APP_TestApplication_Update(FEMTO_Application* application, FEMTO_FrameData* frameData)
{

}

void _APP_TestApplication_Destroy(FEMTO_Application* application)
{

}