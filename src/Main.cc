// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#include <spsdk/Plugin.hh>
#include <spsdk/Logger.hh>

using namespace spsdk;

static IPlugin* PLUGIN = {};

#if defined(LINUX)
    #define PLUGIN_CALL
    #define PLUGIN_EXPORT extern "C" __attribute__((visibility("default")))
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    #define PLUGIN_CALL __stdcall
    #define PLUGIN_EXPORT extern "C"
#endif

SPSDK_GET_PLUGIN();

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
    PLUGIN = _spsdk_getPlugin();

    unsigned int supports = 0x0200 | 0x10000;

    if (PLUGIN->getFlags() & PLUGIN_FLAG_PROCESS_TICK)
        supports |= 0x20000;

    return supports;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void** data) {
    LOGGER = Logger(
        PLUGIN->getPluginName(),
        reinterpret_cast<void (*)(char const*, ...)>(data[0])
    );

    amx_InitLibrary(reinterpret_cast<void**>(data[0x10]));

    return PLUGIN->init();
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
    PLUGIN->free();
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX* amx) {
    return PLUGIN->onAmxLoaded(amx);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* amx) {
    return PLUGIN->onAmxUnload(amx);
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() {
    PLUGIN->processTick();
}
