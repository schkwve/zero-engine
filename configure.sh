#!/usr/bin/env bash

# Set build type
if [[ "${ZERO_ENGINE_BUILD_TYPE}" == "Debug" ||
	  "${ZERO_ENGINE_BUILD_TYPE}" == "Release" ]]; then
	BUILD_TYPE=${ZERO_ENGINE_BUILD_TYPE}
else
	if [[ $1 == "Debug" || $1 == "Release" ]]; then
		BUILD_TYPE=$1
	else
		# Default to Debug
		BUILD_TYPE="Debug"
	fi
fi

# Convert build directory name to all lowercase
BUILD_DIR=build-${BUILD_TYPE,,}
echo $BUILD_DIR

# Print some nice info
echo "[*] Build Type: ${BUILD_TYPE}"
echo "[*] Target Platform: $(uname -s)"

# Make sure there are no old files
rm -rf bin
rm -rf build*

# Create build directory structure
mkdir bin $BUILD_DIR

# Generate CMake configuration
pushd $BUILD_DIR
	cmake -G "Ninja" -DCMAKE_BUILD_TYPE=$BUILD_TYPE ..
popd
if [ $? -ne 0 ]; then
	echo "[!] CMake configuration command failed. Cannot continue."
	exit $?
fi

# Create a symlink to the build folder
ln -s $BUILD_DIR build

# Success
echo "[*] Configuration complete! Enter the 'build' directory to build Zero Engine."