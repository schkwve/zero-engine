/**
 * PROJECT:         Zero Engine
 * FILE:            engine/render/vk_renderer.c
 * DESCRIPTION:     Rendering subsystem Vulkan backend
 * COPYRIGHT:       See LICENSE.md in the top level directory
 * DEVELOPERS:      Jozef Nagy <schkwve@gmail.com>
 */

#include <SDL2/SDL.h>

#include <render/vulkan/vk_renderer.h>
#include <render/vulkan/vk_types.h>

#include <logging.h>
#include <ze_types.h>

/**
 * This function initializes the Vulkan backend.
 * 
 * @return	TRUE if initialization was successful;
 * 			FALSE otherwise.
 */
bool vulkan_initialize()
{
	return true;
}


/**
 * This function cleans up and shuts down the Vulkan backend.
 * 
 * @return	TRUE if shutdown was successful;
 * 			FALSE otherwise.
 */
bool vulkan_shutdown()
{
	return true;
}