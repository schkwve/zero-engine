/**
 * PROJECT:         Zero Engine
 * FILE:            engine/render/renderer.c
 * DESCRIPTION:     Rendering subsystem frontend
 * COPYRIGHT:       LGPL-3.0-only
 * DEVELOPERS:      Jozef Nagy <schkwve@gmail.com>
 */

#include <SDL2/SDL.h>

#include <render/renderer.h>
#include <render/vulkan/vk_renderer.h>

#include <logging.h>
#include <ze_types.h>

/**
 * This function initializes the renderer frontend.
 * It properly sets up related function pointers
 * and prepares the renderer structure for future use.
 *
 * @param	backend
 * 			Renderer backend to be used.
 *
 * @return	TRUE if the renderer backend initialized successfully; or
 * 			FALSE if the renderer backend didn't successfully
 * initialize or the selected renderer doesn't exist.
 */
bool renderer_initialize(const char *app_name, int window_width, int window_height, enum render_backend backend)
{
    // Make sure we don't initialize again
    ZE_ASSERT(renderer.is_initialized == true);

    // Set up renderer structure
    renderer.window_width = window_width;
    renderer.window_height = window_height;
    renderer.window_flags = SDL_WINDOW_HIDDEN;

    // Assign correct function pointers
    switch (backend)
    {
    case RENDERER_VULKAN:
        renderer.backend_initialize = vulkan_initialize;
        renderer.backend_shutdown = vulkan_shutdown;
        renderer.window_flags |= SDL_WINDOW_VULKAN;
        break;
    default:
        FATAL("Renderer type %d does not exist!", backend);
        return false;
    }

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        FATAL("SDL Failed to initialize and the application cannot continue.");
        return false;
    }

    // Create a window
    renderer.window = SDL_CreateWindow(app_name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, renderer.window_width,
                                       renderer.window_height, renderer.window_flags);
    if (!renderer.window)
    {
        FATAL("Couldn't create an SDL window and the application cannot "
              "continue.");
        return false;
    }

    // Initialize backend
    renderer.is_initialized = renderer.backend_initialize(app_name);

    if (renderer.is_initialized)
    {
        // Show initialized window
        SDL_ShowWindow(renderer.window);
    }
    else
    {
        SDL_DestroyWindow(renderer.window);
    }

    // Return
    return renderer.is_initialized;
}

/**
 * This function cleans up and shuts down the renderer subsystem,
 * reseting all function pointers to NULL.
 *
 * @return	Nothing.
 */
void renderer_shutdown()
{
    // Shutdown backend if it was initialized
    if (renderer.is_initialized)
    {
        renderer.backend_shutdown();
    }

    // Destroy window if there is one
    if (renderer.window)
    {
        SDL_DestroyWindow(renderer.window);
    }

    renderer.backend_initialize = NULL;
    renderer.backend_shutdown = NULL;
}