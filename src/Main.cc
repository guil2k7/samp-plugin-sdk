// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#include <spsdk/AmxWrapper.hh>
#include <spsdk/Logger.hh>
#include <spsdk/Plugin.hh>

using namespace spsdk;

static IPlugin* PLUGIN_INSTANCE = {};

#if defined(LINUX)
    #define PLUGIN_CALL
    #define PLUGIN_EXPORT extern "C" __attribute__((visibility("default")))
#elif defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
    #define PLUGIN_CALL __stdcall
    #define PLUGIN_EXPORT extern "C"
#endif

SPSDK_GET_PLUGIN();

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
    PLUGIN_INSTANCE = _spsdk_getPlugin();

    unsigned int supports = 0x0200 | 0x10000;

    if (PLUGIN_INSTANCE->getFlags() & PLUGIN_FLAG_PROCESS_TICK)
        supports |= 0x20000;

    return supports;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void** data) {
    LOGGER = Logger(
        PLUGIN_INSTANCE->getPluginName(),
        reinterpret_cast<void (*)(char const*, ...)>(data[0])
    );

    AmxWrapper::initialize(reinterpret_cast<void**>(data[0x10]));

    return PLUGIN_INSTANCE->init();
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
    PLUGIN_INSTANCE->free();
    AmxWrapper::shutdown();
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX* amx) {
    return PLUGIN_INSTANCE->onAmxLoaded(AmxWrapper::getFromHandle(amx));
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* amx) {
    return PLUGIN_INSTANCE->onAmxUnload(AmxWrapper::getFromHandle(amx));
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() {
    PLUGIN_INSTANCE->processTick();
}
