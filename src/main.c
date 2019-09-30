#include "femto/system.h"

int main(int argc, char *args[])
{
    FEMTO_System* femtoSystem = FEMTO_CreateSystem();
    FEMTO_StartSystem(femtoSystem);
    return 0;
}