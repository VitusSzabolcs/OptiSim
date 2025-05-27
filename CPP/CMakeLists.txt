cmake_minimum_required(VERSION 3.10)

# Project name (for the top-level C++ directory)
project(OptiSim) # Changed name to reflect it's the core C++ component

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# --- Define Source Files ---
# Sources common to both the library and (potentially) the executable
set(COMMON_CPP_SOURCES
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

add_library(OptiSimLib STATIC ${COMMON_CPP_SOURCES})

target_compile_options(OptiSimLib PRIVATE -fPIC)

target_include_directories(OptiSimLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(OptiSim
    #src/main.cpp
    src/OptiSim.cpp
    ${COMMON_CPP_SOURCES}
)

target_link_libraries(OptiSim PRIVATE OptiSimLib)