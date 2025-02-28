// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#include <spsdk/AmxUtils.hh>
#include <spsdk/Logger.hh>
#include <spsdk/Plugin.hh>
#include <spsdk/sampgdk.h>

using namespace spsdk;

static IPlugin* g_pluginInstance = {};

SPSDK_GET_PLUGIN();

// From `amx.cc`.
void amx_InitLibrary(void* const* const ftable);

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
    g_pluginInstance = _spsdk_getPlugin();

    unsigned int supports = sampgdk_Supports() | 0x0200 | 0x10000;

    if (g_pluginInstance->getFlags() & kPluginFlag_ProcessTick)
        supports |= 0x20000;

    return supports;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void** data) {
    if (!sampgdk_Load(data))
        return false;

    LOGGER = Logger(
        g_pluginInstance->getPluginName(),
        reinterpret_cast<void (*)(char const*, ...)>(data[0])
    );

    amx_InitLibrary(reinterpret_cast<void**>(data[0x10]));

    return g_pluginInstance->init();
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
    g_pluginInstance->free();

    sampgdk_Unload();
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX* amx) {
    return g_pluginInstance->onAmxLoaded(amx);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* amx) {
    return g_pluginInstance->onAmxUnload(amx);
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() {
    g_pluginInstance->processTick();
}
