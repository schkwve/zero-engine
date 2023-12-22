/**
 * PROJECT:         Zero Engine
 * FILE:            engine/render/renderer.c
 * DESCRIPTION:     Rendering subsystem frontend
 * COPYRIGHT:       See LICENSE.md in the top level directory
 * DEVELOPERS:      Jozef Nagy <schkwve@gmail.com>
 */

#include <render/vulkan/vk_renderer.h>
#include <render/renderer.h>

#include <logging.h>
#include <ze_types.h>

struct renderer_state renderer = {0};

/**
 * This function initializes the renderer frontend.
 * It properly sets up related function pointers
 * and prepares the renderer structure for future use.
 * 
 * @param	backend
 * 			Renderer backend to be used.
 * 
 * @return	TRUE if the renderer backend initialized successfully; or
 * 			FALSE if the renderer backend didn't successfully initialize or
 * 					the selected renderer doesn't exist.
 */
bool renderer_initialize(enum render_backend backend)
{
	// Assign correct function pointers
	switch(backend) {
	case RENDERER_VULKAN:
		renderer.backend_initialize = vulkan_initialize;
		renderer.backend_shutdown = vulkan_shutdown;
		break;
	default:
		FATAL("Renderer type %d does not exist!", backend);
		return false;
	}

	// Initialize backend
	renderer.is_initialized = renderer.backend_initialize();
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
	renderer.backend_shutdown();

	renderer.backend_initialize = NULL;
	renderer.backend_shutdown = NULL;
}