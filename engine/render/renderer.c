#include <render/vulkan/vk_renderer.h>

#include <render/renderer.h>
#include <logging.h>
#include <ze_types.h>

struct renderer_state renderer;

bool renderer_initialize(enum render_backend type)
{
	// Assign correct function pointers
	switch(type) {
	case RENDERER_VULKAN:
		renderer.backend_initialize = vulkan_initialize;
		renderer.backend_shutdown = vulkan_shutdown;
		break;
	default:
		FATAL("Renderer type %d does not exist!", type);
		return false;
	}

	// Initialize backend
	return renderer.backend_initialize();
}

void renderer_shutdown()
{
	renderer.backend_shutdown();

	renderer.backend_initialize = NULL;
	renderer.backend_shutdown = NULL;
}