/**
 * PROJECT:         Zero Engine
 * FILE:            testgame/main.c
 * DESCRIPTION:     Zero Engine test game entry point
 * COPYRIGHT:       LGPL-3.0-only
 * DEVELOPERS:      Jozef Nagy <schkwve@gmail.com>
 */

#include <ze_engine.h>

int main(void)
{
    engine_initialize("Zerø Engine Test Game");
    engine_run();
    engine_shutdown(0);
    return 0;
}
