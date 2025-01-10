cmake_minimum_required(VERSION 3.22)
project("SA-MP Plugin SDK" VERSION 0.1.0 LANGUAGES C CXX)

set(SPSDK_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(SPSDK_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(SPSDK_VERSION_PATCH ${PROJECT_VERSION_PATCH})

option(SPSDK_32BITS "Build the SDK for 32 bits" ON)

if(SPSDK_32BITS)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
endif()

add_subdirectory(src)
add_subdirectory(examples)
