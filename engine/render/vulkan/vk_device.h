#pragma once

#include <vulkan/vulkan.h>

#include <stdint.h>

#include <ze_types.h>

typedef struct _queue_family_indices
{
    bool is_graphics_family_present;
    uint32_t graphics_family;
} queue_family_indices;

bool vulkan_device_is_suitable(VkPhysicalDevice device);
queue_family_indices find_queue_families(VkPhysicalDevice device);