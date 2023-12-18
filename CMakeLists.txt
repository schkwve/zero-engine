# Set minimum CMake version
cmake_minimum_required(VERSION 3.27.6)

# Set project name
project(zero_engine)

# Set the standard to C++17
set(CMAKE_CXX_STANDARD 17)

# Vulkan is required to build this engine... obviously :p
find_package(Vulkan REQUIRED)

# Optional GLSL Validator
find_program(GLSL_VALIDATOR glslangValidator HINTS /usr/bin /usr/local/bin $ENV{VULKAN_SDK}/Bin $ENV{VULKAN_SDK}/Bin32)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

# Add Engine library
add_subdirectory(engine)

# Add Testgame executable
add_subdirectory(testgame)

# Add Editor executable
add_subdirectory(editor)

# Find all shader files
file(GLOB_RECURSE GLSL_SOURCE_FILES
	"${PROJECT_SOURCE_DIR}/shaders/*.frag"
	"${PROJECT_SOURCE_DIR}/shaders/*.vert"
	"${PROJECT_SOURCE_DIR}/shaders/*.comp"
)

# Build shaders
foreach(GLSL ${GLSL_SOURCE_FILES})
	get_filename_component(FILENAME ${GLSL} NAME)
	message(STATUS "Building ${FILENAME}.spv... ")
	set(SPIRV "${PROJECT_SOURCE_DIR}/shaders/${FILENAME}.spv")
	message(STATUS ${GLSL})
	add_custom_command(
		OUTPUT ${SPIRV}
		COMMAND ${GLSL_VALIDATOR} -V ${GLSL} -o ${SPIRV}
		DEPENDS ${GLSL}
	)
	list(APPEND SPIRV_BINARY_FILES ${SPIRV})
endforeach(GLSL)

add_custom_target(
	shaders
	DEPENDS ${SPIRV_BINARY_FILES}
)