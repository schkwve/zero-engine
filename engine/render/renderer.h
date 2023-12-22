/**
 * PROJECT:         Zero Engine
 * FILE:            engine/render/renderer.h
 * DESCRIPTION:     Rendering subsystem frontend
 * COPYRIGHT:       See LICENSE.md in the top level directory
 * DEVELOPERS:      Jozef Nagy <schkwve@gmail.com>
 */

#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>

#include <ze_types.h>

enum render_backend {
	RENDERER_VULKAN,
};

struct renderer_state {
	bool (*backend_initialize)();
	bool (*backend_shutdown)();

	struct SDL_Window *window;
	int window_width;
	int window_height;
	SDL_WindowFlags window_flags;

	bool is_initialized;
};

bool renderer_initialize(const char *app_name, int window_width, int window_height, enum render_backend backend);
void renderer_shutdown();

#endif /* RENDERER_H */
