project(engine)

add_library(engine SHARED ze_engine.cpp)

target_include_directories(engine
		PUBLIC
			$<INSTALL_INTERFACE:.>
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		PRIVATE
			${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(engine Vulkan::Vulkan)

add_dependencies(engine shaders)