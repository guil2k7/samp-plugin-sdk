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

#if defined LINUX
    #define PLUGIN_CALL
    #define PLUGIN_EXPORT PLUGIN_EXTERN_C __attribute__((visibility("default")))
#elif defined WIN32 || defined _WIN32 || defined __WIN32__
    #define PLUGIN_CALL __stdcall
    #define PLUGIN_EXPORT PLUGIN_EXTERN_C
#endif
