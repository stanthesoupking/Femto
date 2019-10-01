#include "applications/hidden/bar.h"

#include <stdlib.h>

#include "femto/views/button.h"
#include "femto/views/canvas_layout.h"

// Internal bar methods
void _Update(FEMTO_Application* application, FEMTO_FrameData* frameData);
void _Destroy(FEMTO_Application* application);

FEMTO_Application* APP_SpawnBar(FEMTO_System* system)
{
    APP_Bar_Data* data = (APP_Bar_Data*) malloc(sizeof(struct APP_Bar_Data_int));

    FEMTO_Screen** screens = (FEMTO_Screen**) malloc(sizeof(FEMTO_Screen*) * 1);

    FEMTO_View* root = FEMTO_CreateCanvasLayout("PanelCanvas", NULL, system->renderer, (SDL_Rect) {0, 0, 800, 26});
    FEMTO_SetCanvasLayoutFillColour(root, FEMTO_CreateColour(0.8f, 0.8f, 0.8f, 1.0f));
    FEMTO_SetCanvasLayoutFill(root, true);

    FEMTO_View* launcherButton = FEMTO_CreateButton("LauncherButton", root,
        system->renderer, system->textRenderer, "Launch",
        (SDL_Rect) {2, 2, 70, 22});

    FEMTO_Screen* screen = FEMTO_CreateScreen(root);
    screens[0] = screen;

    FEMTO_Application* application = FEMTO_CreateApplication(system, "_Femto_Bar", data, screens, 0, _Update, _Destroy);

    return application;
}

void _Update(FEMTO_Application* application, FEMTO_FrameData* frameData)
{
    // Update root element
    FEMTO_UpdateView(application->screens[application->activeScreen]->root, frameData);
}

void _Destroy(FEMTO_Application* application)
{

}