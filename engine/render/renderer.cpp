#include <render/vulkan/vk_renderer.h>

#include <render/renderer.h>
#include <logging.h>

bool Renderer::Initialize(RendererType type)
{
	// Assign correct function pointers
	switch(type) {
	case RENDERER_VULKAN:
		InitializeBackend = VulkanRenderer::InitializeBackend();
		ShutdownBackend = VulkanRenderer::ShutdownBackend();
		break;
	default:
		//Log::FATAL("Renderer type %d does not exist!", type);
		return false;
	}

	// Initialize backend
	// return InitializeBackend();
	return true;
}

void Renderer::Shutdown()
{
	// ShutdownBackend();

	// InitializeBackend = NULL;
	// ShutdownBackend = NULL;
}