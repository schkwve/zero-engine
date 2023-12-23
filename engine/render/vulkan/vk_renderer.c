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
    unsigned int extension_num = 0;
    SDL_Vulkan_GetInstanceExtensions(renderer.window, &extension_num, NULL);
    const char **extension_names = darray_reserve(const char *, extension_num);
    SDL_Vulkan_GetInstanceExtensions(renderer.window, NULL, extension_names);
    darray_push(extension_names, &VK_KHR_SURFACE_EXTENSION_NAME);

    VkInstanceCreateInfo create_info = {0};
#ifdef __APPLE__
    create_info.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    darray_push(extension_names, &"VK_EXT_metal_surface");
    darray_push(extension_names, &VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
#endif
#ifdef __DEBUG__
    darray_push(extension_names, &VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    uint32_t extension_count = darray_length(extension_names);
    DEBUG("Vulkan extensions (%d total):", extension_count);
    for (size_t i = 0; i < extension_count; i++)
    {
        DEBUG("    %s", extension_names[i]);
    }
#endif
    create_info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    create_info.pApplicationInfo = &app_info;
    create_info.enabledExtensionCount = darray_length(extension_names);
    create_info.ppEnabledExtensionNames = extension_names;

    uint32_t layer_count = 0;
    const char **layer_names = 0;

/*
#ifdef __DEBUG__
    layer_names = darray_create(const char *);

    uint32_t available_layer_count = 0;
    VK_CHECK(vkEnumerateInstanceLayerProperties(&available_layer_count, 0));
    VkLayerProperties *available_layer_names = darray_reserve(VkLayerProperties, available_layer_count);
    VK_CHECK(vkEnumerateInstanceLayerProperties(&available_layer_count, available_layer_names));
    darray_push(layer_names, &"VK_LAYER_KHRONOS_validation");

    layer_count = darray_length(layer_names);
    for (uint32_t i = 0; i < layer_count; i++)
    {
        bool found = false;
        for (uint32_t j = 0; j < layer_count; j++)
        {
            if (strcmp(layer_names[i], available_layer_names[i].layerName) == 0)
            {
                found = true;
                DEBUG("Validation layer '%s' OK.", layer_names[i]);
                break;
            }
        }

        if (!found)
        {
            FATAL("Required validation layer '%s' is missing.", layer_names[i]);
            return false;
        }
    }
#endif
*/

    create_info.enabledLayerCount = layer_count;
    create_info.ppEnabledLayerNames = layer_names;

    // Create instance
    VK_CHECK(vkCreateInstance(&create_info, NULL, &vk_state.instance));

    INFO("Created Vulkan instance");

    VkPhysicalDevice physical_device = VK_NULL_HANDLE;
    uint32_t device_count = 0;

    VK_CHECK(vkEnumeratePhysicalDevices(vk_state.instance, &device_count, NULL));
    if (device_count == 0)
    {
        FATAL("No GPUs found!");
        return false;
    }

    VkPhysicalDevice *devices = darray_reserve(VkPhysicalDevice, device_count);
    VK_CHECK(vkEnumeratePhysicalDevices(vk_state.instance, &device_count, devices));

    for (size_t i = 0; i < device_count; i++)
    {
        INFO("Testing GPU %d...", i);
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