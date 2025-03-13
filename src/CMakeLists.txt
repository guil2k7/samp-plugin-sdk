option(SPSDK_INCLUDE_SAMPGDB "Include the sampgdk in the SDK" ON)

set(SPSDK_SOURCE_FILES
    amx.cc
    Utils.cc
    Logger.cc
    Main.cc
    Value.cc
    VariadicArgs.cc
    Exports.def
)

set(SPSDK_DEFINTIONS
    -DSPSDK_VERSION_MAJOR=${SPSDK_VERSION_MAJOR}
    -DSPSDK_VERSION_MINOR=${SPSDK_VERSION_MINOR}
    -DSPSDK_VERSION_PATCH=${SPSDK_VERSION_PATCH}
    -DHAVE_STDINT_H=1
)

if(SPSDK_INCLUDE_SAMPGDB)
    list(APPEND SPSDK_SOURCE_FILES sampgdk.c)
    list(APPEND SPSDK_DEFINTIONS -DSPSDK_INCLUDE_SAMPGDB -DSAMPGDK_AMALGAMATION)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    list(APPEND SPSDK_DEFINTIONS -DLINUX=1)
endif()

add_library(samp-plugin-sdk STATIC ${SPSDK_SOURCE_FILES})
target_include_directories(samp-plugin-sdk PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_definitions(samp-plugin-sdk PUBLIC ${SPSDK_DEFINTIONS})
