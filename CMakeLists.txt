cmake_minimum_required(VERSION 3.22)
project("SA-MP Plugin SDK" VERSION 0.2.0 LANGUAGES C CXX)

set(SPSDK_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(SPSDK_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(SPSDK_VERSION_PATCH ${PROJECT_VERSION_PATCH})

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(src)

option(SPSDK_BUILD_EXAMPLES "Build examples" ON)
option(SPSDK_INCLUDE_SAMPGDK "Include the sampgdk in the SDK" OFF)

if(SPSDK_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
