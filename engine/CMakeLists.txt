project(engine)

add_library(engine SHARED ze_engine.cpp)

SET(CMAKE_CXX_FLAGS_DEBUG "-g -D__DEBUG__")
SET(CMAKE_CXX_FLAGS_RELEASE "-O3")

target_include_directories(engine
		PUBLIC
			$<INSTALL_INTERFACE:.>
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		PRIVATE
			${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(engine Vulkan::Vulkan)

add_dependencies(engine shaders)