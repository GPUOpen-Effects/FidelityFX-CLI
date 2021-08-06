# Copyright (c) 2021 Advanced Micro Devices, Inc. All rights reserved.

project(FidelityFX_CLI)

# enable multi-threaded compilation
add_compile_options(/MP)

# Check for Visual Studio 2019's build tooling
if(MSVC_TOOLSET_VERSION VERSION_LESS 142)
    message(FATAL_ERROR "Cannot find MSVC toolset version 142 or greater. Please make sure Visual Studio 2019 or newer installed")
endif()

# generate the output binary in the /bin directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)

# set sources
set(sources
    FidelityFX_CLI.cpp
    pch.hpp
    pch.cpp)

# setup target binary
add_executable(${PROJECT_NAME} ${sources})

# add link time dependencies
target_link_libraries(${PROJECT_NAME} PRIVATE d3d11.lib windowscodecs.lib)