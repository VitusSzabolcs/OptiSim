# Python/CMakeLists.txt
cmake_minimum_required(VERSION 3.15...3.27)
project(OptiSimPythonBindings CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(pybind11 CONFIG REQUIRED)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)


set(OptiSim_DIR "${CMAKE_SOURCE_DIR}/../CPP/build")
find_library(OptiSim_LIB OptiSimLib HINTS ${OptiSim_DIR} NO_DEFAULT_PATH)
if(NOT OptiSim_LIB)
    message(FATAL_ERROR "Could not find OptiSim library. Make sure it's built in ${OptiSim_DIR}")
endif()
set(OptiSim_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/../CPP/include")

set(OPTISIM_BINDING_SOURCES
    bind/optisim_bindings.cpp
    bind/bind_imaging_subjects.cpp
    bind/bind_optical_objects.cpp
    bind/bind_optical_system.cpp
)

set(COMPILED_MODULE_NAME optisim)

pybind11_add_module(${COMPILED_MODULE_NAME}
    ${OPTISIM_BINDING_SOURCES}
)

target_link_libraries(${COMPILED_MODULE_NAME} PRIVATE ${OptiSim_LIB})

target_include_directories(${COMPILED_MODULE_NAME} PRIVATE
    ${OptiSim_INCLUDE_DIR}
)
