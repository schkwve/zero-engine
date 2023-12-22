/**
 * PROJECT:         Zero Engine
 * FILE:            engine/render/renderer.h
 * DESCRIPTION:     Rendering subsystem frontend
 * COPYRIGHT:       See LICENSE.md in the top level directory
 * DEVELOPERS:      Jozef Nagy <schkwve@gmail.com>
 */

#ifndef RENDERER_H
#define RENDERER_H

#include <ze_types.h>

enum render_backend {
	RENDERER_VULKAN,
};

struct renderer_state {
	bool (*backend_initialize)();
	bool (*backend_shutdown)();

	bool is_initialized;
};

bool renderer_initialize(enum render_backend type);
void renderer_shutdown();

#endif /* RENDERER_H */
