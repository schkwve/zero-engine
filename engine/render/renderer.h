#pragma once

enum RendererType {
	RENDERER_VULKAN,
};

class Renderer {
private:
	static bool (*InitializeBackend)();
	static bool (*ShutdownBackend)();

public:
	static bool Initialize(RendererType type);
	static void Shutdown();
};