project(engine)

add_library(engine SHARED
						ze_engine.c
						cont/darray.c
						render/renderer.c
						render/vulkan/vk_renderer.c
						render/vulkan/vk_device.c
						render/vulkan/vk_swapchain.c
						)

SET(CMAKE_C_FLAGS_DEBUG "-g -D__DEBUG__")
SET(CMAKE_C_FLAGS_RELEASE "-O3")

if(APPLE)
	add_definitions(-D__APPLE__)
elseif(UNIX)
	add_definitions(-D__UNIX__)
elseif(WIN32)
	add_definitions(-D__WIN32__)
endif()

target_include_directories(engine
		PUBLIC
			$<INSTALL_INTERFACE:.>
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		PRIVATE
			${SDL2_INCLUDE_DIRS}
			${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(engine PUBLIC ${SDL2_LIBRARIES} Vulkan::Vulkan)

add_dependencies(engine shaders)