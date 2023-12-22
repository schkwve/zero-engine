#include <ze_engine.h>
#include <logging.h>

#include <render/renderer.h>

/**
 * This function initializes the engine.
 * 
 * @return	Nothing.
 */
void engine_initialize()
{
	if (!renderer_initialize(RENDERER_VULKAN)) {
		FATAL("The rendering subsystem failed to initialize and Zero Engine cannot continue. Exitting...");
		engine_shutdown();
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
