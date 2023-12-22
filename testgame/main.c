/**
 * PROJECT:         Zero Engine
 * FILE:            testgame/main.c
 * DESCRIPTION:     Zero Engine test game entry point
 * COPYRIGHT:       See LICENSE.md in the top level directory
 * DEVELOPERS:      Jozef Nagy <schkwve@gmail.com>
 */

#include <ze_engine.h>

int main(void)
{
	engine_initialize("Zerø Engine Test Game");
	engine_run();
	engine_shutdown();
	return 0;
}
