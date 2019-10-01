#include "applications/hidden/bar.h"

#include <stdlib.h>

#include "femto/views/button.h"
#include "femto/views/canvas_layout.h"

// Internal bar methods
void _APP_Bar_Update(FEMTO_Application* application, FEMTO_FrameData* frameData);
void _APP_Bar_Destroy(FEMTO_Application* application);

FEMTO_Application* APP_SpawnBar(FEMTO_System* system)
{
    APP_Bar_Data* data = (APP_Bar_Data*) malloc(sizeof(struct APP_Bar_Data_int));

    FEMTO_Screen** screens = (FEMTO_Screen**) malloc(sizeof(FEMTO_Screen*) * 1);
    
    FEMTO_Application* application = FEMTO_CreateApplication(system, "_Femto_Bar", data, screens, 0, _APP_Bar_Update, _APP_Bar_Destroy);
    application->rect.h = application->rect.y;
    application->rect.y = 0;

    FEMTO_View* root = FEMTO_CreateCanvasLayout("PanelCanvas", application, NULL);
    FEMTO_SetCanvasLayoutFillColour(root, FEMTO_CreateColour(0.29f, 0.25f, 0.29f, 1.0f));
    FEMTO_SetCanvasLayoutFill(root, true);

    FEMTO_View* launcherButton = FEMTO_CreateButton("LauncherButton", application, root,
        system->textRenderer, "Launch");

    FEMTO_SetViewAbsoluteRect(launcherButton,
        (SDL_Rect) {2, 2, 70, 22});

    FEMTO_Screen* screen = FEMTO_CreateScreen(root);
    screens[0] = screen;

    return application;
}

void _APP_Bar_Update(FEMTO_Application* application, FEMTO_FrameData* frameData)
{

}

void _APP_Bar_Destroy(FEMTO_Application* application)
{

}