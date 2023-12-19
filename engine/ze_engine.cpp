#include <ze_engine.h>
#include <logging.h>

#include <render/renderer.h>

/**
 * This function initializes the engine.
 * 
 * @return	This routine does not return any value.
 */
void ZeroEngine::Initialize()
{
	Log::DEBUG("Hello, World!");
	//RenderFrontend::Initialize(...);
}

/**
 * This function cleans up and shuts down the engine.
 * 
 * @return	This routine does not return any value.
 */
void ZeroEngine::Shutdown()
{
}
