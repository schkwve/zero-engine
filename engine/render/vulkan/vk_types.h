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
