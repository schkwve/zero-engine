/**
 * PROJECT:         Zero Engine
 * FILE:            engine/ze_engine.c
 * DESCRIPTION:     Zero Engine entry/shutdown points
 * COPYRIGHT:       LGPL-3.0-only
 * DEVELOPERS:      Jozef Nagy <schkwve@gmail.com>
 */

#include <logging.h>
#include <ze_engine.h>

#include <render/renderer.h>

/**
 * This function initializes the engine.
 *
 * @return	Nothing.
 */
void engine_initialize(const char *app_name)
{
    // Initialize rendering subsystem
    // -> Set window size to 1280x720
    if (!renderer_initialize(app_name, 1280, 720, RENDERER_VULKAN))
    {
        FATAL("The rendering subsystem failed to initialize and Zero Engine "
              "cannot continue. Exitting...");
        engine_shutdown();
    }
}

/**
 * This function is the main game loop.
 *
 * @return	Nothing.
 */
void engine_run()
{
    SDL_Event e;
    bool should_quit = false;

    while (!should_quit)
    {
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
            {
                should_quit = true;
            }
        }

        // engine_redraw();
    }
}

/**
 * This function cleans up and shuts down the engine.
 *
 * @return	Nothing.
 */
void engine_shutdown()
{
    renderer_shutdown();
}
