set(SPSDK_SOURCE_FILES
    amx.cc
    AmxWrapper.cc
    Logger.cc
    Main.cc
    sampgdk.c
    Value.cc
    VariadicArgs.cc
    Exports.def
)

set(SPSDK_DEFINTIONS
    -DSPSDK_VERSION_MAJOR=${SPSDK_VERSION_MAJOR}
    -DSPSDK_VERSION_MINOR=${SPSDK_VERSION_MINOR}
    -DSPSDK_VERSION_PATCH=${SPSDK_VERSION_PATCH}
    -DHAVE_STDINT_H=1
    -DSAMPGDK_AMALGAMATION
    -DSAMPGDK_CPP_WRAPPERS
)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    list(APPEND SPSDK_DEFINTIONS -DLINUX=1)
endif()

add_library(samp-plugin-sdk STATIC ${SPSDK_SOURCE_FILES})
target_include_directories(samp-plugin-sdk PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_definitions(samp-plugin-sdk PUBLIC ${SPSDK_DEFINTIONS})
