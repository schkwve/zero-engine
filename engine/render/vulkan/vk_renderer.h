#pragma once

#include <render/renderer.h>

class VulkanRenderer : public Renderer {
public:
	bool InitializeBackend();
	bool ShutdownBackend();
};
