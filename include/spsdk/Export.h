// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#pragma once

#if defined __cplusplus
    #define PLUGIN_EXTERN_C extern "C"
#else
    #define PLUGIN_EXTERN_C
#endif

#if defined __GNUC__
    #define PLUGIN_EXPORT PLUGIN_EXTERN_C __attribute__((visibility("default")))
#elif defined _MSC_VER
    #define PLUGIN_EXPORT PLUGIN_EXTERN_C __declspec(dllexport)
#else
    #error unsupported compiler
#endif

#if defined _WIN32 || defined __CYGWIN__
    #define PLUGIN_CALL __stdcall
#elif defined __unix__
    #define PLUGIN_CALL
#else
    #error unsupported platform
#endif
