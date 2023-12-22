/**
 * PROJECT:         Zero Engine
 * FILE:            engine/render/vk_renderer.h
 * DESCRIPTION:     Rendering subsystem Vulkan backend
 * COPYRIGHT:       LGPL-3.0-only
 * DEVELOPERS:      Jozef Nagy <schkwve@gmail.com>
 */

#pragma once

#include <vulkan/vk_enum_string_helper.h>
#include <vulkan/vulkan.h>

#include <ze_types.h>

#define VK_CHECK(x)                                                                                                    \
    do                                                                                                                 \
    {                                                                                                                  \
        VkResult error = x;                                                                                            \
        if (error != VK_SUCCESS)                                                                                       \
        {                                                                                                              \
            FATAL("Vulkan Error (%s)", string_VkResult(error));                                                        \
            abort();                                                                                                   \
        }                                                                                                              \
    } while (0);

struct vulkan_state
{
    VkInstance instance;
    VkDebugUtilsMessengerEXT debug_messenger;

    VkPhysicalDevice chosen_gpu;
    VkDevice device;

    VkSurfaceKHR window_surface;
};

static struct vulkan_state vk_state = {0};

bool vulkan_initialize(const char *app_name);
bool vulkan_shutdown();
