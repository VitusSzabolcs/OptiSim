cmake_minimum_required(VERSION 3.10)

# Project name
project(OptiSim)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include header files from 'include' directory
include_directories(include)

# Add the source files
add_executable(OptiSim
	src/main.cpp
	src/Image.cpp
	src/ImagingSubject.cpp
	src/Lens.cpp
	src/LightSource.cpp
	src/OpticalObject.cpp
	src/ThickLens.cpp
	src/ThinLens.cpp
	src/OpticalSystem.cpp
	src/OptiSimVersion.cpp
)
