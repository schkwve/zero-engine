/**
 * PROJECT:         Zero Engine
 * FILE:            engine/render/vk_renderer.c
 * DESCRIPTION:     Rendering subsystem Vulkan backend
 * COPYRIGHT:       LGPL-3.0-only
 * DEVELOPERS:      Jozef Nagy <schkwve@gmail.com>
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_vulkan.h>

#include <cont/darray.h>

#include <render/renderer.h>
#include <render/vulkan/vk_device.h>
#include <render/vulkan/vk_renderer.h>

#include <logging.h>
#include <ze_types.h>

/**
 * This function initializes the Vulkan backend.
 *
 * @return	TRUE if initialization was successful;
 * 			FALSE otherwise.
 */
bool vulkan_initialize(const char *app_name)
{
    VkApplicationInfo app_info = {0};
    app_info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    app_info.pApplicationName = app_name;
    app_info.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    app_info.pEngineName = "Zero Engine";
    app_info.engineVersion = VK_MAKE_VERSION(0, 0, 1);
    app_info.apiVersion = VK_API_VERSION_1_3;

    // Extensions
    unsigned int extension_count = 0;
    SDL_Vulkan_GetInstanceExtensions(renderer.window, &extension_count, NULL);
    const char **extension_names = darray_create(const char *);
    SDL_Vulkan_GetInstanceExtensions(renderer.window, &extension_count, extension_names);

    VkInstanceCreateInfo create_info = {0};
#if __APPLE__
    create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    darray_push(extension_names, &"VK_EXT_metal_surface");
    darray_push(extension_names, &VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
#endif
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;
    create_info.enabledExtensionCount = extension_count;
    create_info.ppEnabledExtensionNames = extension_names;
    create_info.enabledLayerCount = 0;

    // Create instance
    VK_CHECK(vkCreateInstance(&create_info, NULL, &vk_state.instance));

    INFO("Created Vulkan instance");

#ifdef __DEBUG__
    DEBUG("Vulkan extensions:");
    for (size_t i = 0; i < darray_length(extension_names); i++)
    {
        DEBUG("    %s", extension_names[i]);
    }
#endif

    VkPhysicalDevice physical_device = VK_NULL_HANDLE;
    uint32_t device_count = 0;

    vkEnumeratePhysicalDevices(vk_state.instance, &device_count, NULL);
    if (device_count == 0)
    {
        FATAL("No GPUs found!");
        return false;
    }

    VkPhysicalDevice *devices = darray_create(VkPhysicalDevice);
    vkEnumeratePhysicalDevices(vk_state.instance, &device_count, devices);

    for (size_t i = 0; i < device_count; i++)
    {
        DEBUG("Testing GPU %d...", i);
        if (vulkan_device_is_suitable(devices[i]))
        {
            physical_device = devices[i];
            break;
        }
    }

    if (physical_device == VK_NULL_HANDLE)
    {
        FATAL("Failed to find a suitable GPU!");
        return false;
    }

    return true;
}

/**
 * This function cleans up and shuts down the Vulkan backend.
 *
 * @return	TRUE if shutdown was successful;
 * 			FALSE otherwise.
 */
bool vulkan_shutdown()
{
    vkDestroyInstance(vk_state.instance, NULL);
    return true;
}