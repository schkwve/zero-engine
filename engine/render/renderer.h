/**
 * PROJECT:         Zero Engine
 * FILE:            engine/render/renderer.h
 * DESCRIPTION:     Rendering subsystem frontend
 * COPYRIGHT:       LGPL-3.0-only
 * DEVELOPERS:      Jozef Nagy <schkwve@gmail.com>
 */

#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>

#include <ze_types.h>

enum render_backend
{
    RENDERER_VULKAN,
};

struct renderer_state
{
    bool (*backend_initialize)(const char *);
    bool (*backend_shutdown)();

    struct SDL_Window *window;
    int window_width;
    int window_height;
    SDL_WindowFlags window_flags;

    bool is_initialized;
};

static struct renderer_state renderer = {0};

bool renderer_initialize(const char *app_name, int window_width, int window_height, enum render_backend backend);
void renderer_shutdown();

#endif /* RENDERER_H */
