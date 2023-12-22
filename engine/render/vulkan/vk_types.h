/**
 * PROJECT:         Zero Engine
 * FILE:            engine/render/vk_types.h
 * DESCRIPTION:     Vulkan-related structures and macros definitions
 * COPYRIGHT:       See LICENSE.md in the top level directory
 * DEVELOPERS:      Jozef Nagy <schkwve@gmail.com>
 */

#pragma once

#include <logging.h>

#define VK_CHECK(x) \
	do { \
		VkResult error = x; \
		if (error) { \
			FATAL("Vulkan Error (%s)", string_VkResult(error)); \
			abort(); \
		} \
	} while(0);
