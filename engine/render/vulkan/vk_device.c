#include <vulkan/vulkan.h>

#include <render/vulkan/vk_device.h>
#include <render/vulkan/vk_renderer.h>

#include <logging.h>
#include <ze_types.h>

bool vulkan_device_is_suitable(VkPhysicalDevice device)
{
    queue_family_indices indices = find_queue_families(device);
    return indices.is_graphics_family_present;
}

queue_family_indices find_queue_families(VkPhysicalDevice device)
{
    queue_family_indices indices = {0};
    uint32_t queue_family_count = 0;

    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, NULL);
    VkQueueFamilyProperties queue_families[queue_family_count];
    vkGetPhysicalDeviceQueueFamilyProperties(device, &queue_family_count, queue_families);

    DEBUG("Queue Family Count: %d", queue_family_count);

    for (int i = 0; i < queue_family_count; i++)
    {
        if (queue_families[i].queueFlags & VK_QUEUE_GRAPHICS_BIT)
        {
            DEBUG("Graphics Queue Family: %d", i);
            indices.is_graphics_family_present = true;
            indices.graphics_family = i;
            break;
        }
    }

    return indices;
}