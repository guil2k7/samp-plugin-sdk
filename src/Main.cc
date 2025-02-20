// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#include <spsdk/AmxWrapper.hh>
#include <spsdk/Logger.hh>
#include <spsdk/Plugin.hh>
#include <spsdk/sampgdk.h>

using namespace spsdk;

static IPlugin* PLUGIN_INSTANCE = {};

SPSDK_GET_PLUGIN();

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
    PLUGIN_INSTANCE = _spsdk_getPlugin();

    unsigned int supports = sampgdk::Supports() | 0x0200 | 0x10000;

    if (PLUGIN_INSTANCE->getFlags() & PLUGIN_FLAG_PROCESS_TICK)
        supports |= 0x20000;

    return supports;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void** data) {
    if (!sampgdk::Load(data))
        return false;

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

    sampgdk::Unload();
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
