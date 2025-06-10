cmake_minimum_required(VERSION 3.10)

# Project name (for the top-level C++ directory)
project(OptiSim) # Changed name to reflect it's the core C++ component

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(OptiSim_DIR "${CMAKE_SOURCE_DIR}/../../CPP/build")
find_library(OptiSim_LIB OptiSimLib HINTS ${OptiSim_DIR} )

# --- Define Source Files ---
# Sources common to both the library and (potentially) the executable



add_executable(OptiSimTest
    test.cpp
    
)

target_link_libraries(OptiSimTest PRIVATE ${OptiSim_LIB})

target_include_directories(OptiSimTest PRIVATE
    ${CMAKE_SOURCE_DIR}/../../CPP/include
)