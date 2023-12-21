#pragma once

#include <ze_types.h>

enum render_backend {
	RENDERER_VULKAN,
};

struct renderer_state {
	bool (*backend_initialize)();
	bool (*backend_shutdown)();
};

bool renderer_initialize(enum render_backend type);
void renderer_shutdown();
