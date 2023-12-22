project(engine)

add_library(engine SHARED
						ze_engine.c
						render/renderer.c
						render/vulkan/vk_renderer.c
						)

SET(CMAKE_C_FLAGS_DEBUG "-g -D__DEBUG__")
SET(CMAKE_C_FLAGS_RELEASE "-O3")

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