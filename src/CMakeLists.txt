set(SPSDK_SOURCE_FILES
    amx/amx.cc
    Logger.cc
    Main.cc
)

set(SPSDK_DEFINTIONS
    -DSPSDK_VERSION_MAJOR=${MIRAGE_VERSION_MAJOR}
    -DSPSDK_VERSION_MINOR=${MIRAGE_VERSION_MINOR}
    -DSPSDK_VERSION_PATCH=${MIRAGE_VERSION_PATCH}
    -DHAVE_STDINT_H=1
)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    list(APPEND SPSDK_DEFINTIONS -DLINUX=1)
endif()

add_library(samp-plugin-sdk SHARED ${SPSDK_SOURCE_FILES})
target_include_directories(samp-plugin-sdk PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_definitions(samp-plugin-sdk PUBLIC ${SPSDK_DEFINTIONS})
