#include <ze_engine.h>
#include <logging.h>

#include <render/renderer.h>

/**
 * This function initializes the engine.
 * 
 * @return	This routine does not return any value.
 */
void engine_initialize()
{
	renderer_initialize(RENDERER_VULKAN);
}

/**
 * This function cleans up and shuts down the engine.
 * 
 * @return	This routine does not return any value.
 */
void engine_shutdown()
{
	renderer_shutdown();
}
