// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#include <spsdk/Utils.hh>
#include <spsdk/Logger.hh>
#include <spsdk/Plugin.hh>
#include <spsdk/sampgdk.h>

using namespace spsdk;

static IPlugin* plugin = {};

SPSDK_GET_PLUGIN();

// From `amx.cc`.
void amx_InitLibrary(void* const* const ftable);

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
    plugin = _spsdk_getPlugin();

    unsigned int supports = sampgdk_Supports() | 0x0200 | 0x10000;

    if (plugin->getFlags() & kPluginFlag_ProcessTick)
        supports |= 0x20000;

    return supports;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void** data) {
    if (!sampgdk_Load(data))
        return false;

    logger = Logger(
        plugin->getPluginName(),
        reinterpret_cast<void (*)(char const*, ...)>(data[0])
    );

    amx_InitLibrary(reinterpret_cast<void**>(data[0x10]));

    return plugin->init();
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
    plugin->free();

    sampgdk_Unload();
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX* amx) {
    return plugin->onAmxLoaded(amx);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* amx) {
    return plugin->onAmxUnload(amx);
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() {
    sampgdk_ProcessTick();
    plugin->processTick();
}
