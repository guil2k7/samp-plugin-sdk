// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#include <spsdk/Utils.hh>
#include <spsdk/Logger.hh>
#include <spsdk/Plugin.hh>
#include <spsdk/PluginExport.h>

#ifdef SPSDK_INCLUDE_SAMPGDB
#include <spsdk/sampgdk.h>
#endif

using namespace spsdk;

static IPlugin* plugin = {};

SPSDK_GET_PLUGIN();

// From `amx.cc`.
void amx_InitLibrary(void* const* const ftable);

PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports() {
    plugin = _spsdk_getPlugin();

    unsigned int supports = 0x0200 | 0x10000;

    #ifdef SPSDK_INCLUDE_SAMPGDB
    supports |= sampgdk_Supports();
    #endif

    if (plugin->getFlags() & PLUGIN_FLAG_PROCESS_TICK)
        supports |= 0x20000;

    return supports;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void** data) {
    #ifdef SPSDK_INCLUDE_SAMPGDB
    if (!sampgdk_Load(data))
        return false;
    #endif

    Logger::global = Logger(
        plugin->getPluginName(),
        reinterpret_cast<void (*)(char const*, ...)>(data[0])
    );

    amx_InitLibrary(reinterpret_cast<void**>(data[0x10]));

    return plugin->init();
}

PLUGIN_EXPORT void PLUGIN_CALL Unload() {
    plugin->free();

    #ifdef SPSDK_INCLUDE_SAMPGDB
    sampgdk_Unload();
    #endif
}

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX* amx) {
    return plugin->onAmxLoaded(amx);
}

PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX* amx) {
    return plugin->onAmxUnload(amx);
}

PLUGIN_EXPORT void PLUGIN_CALL ProcessTick() {
    #ifdef SPSDK_INCLUDE_SAMPGDB
    sampgdk_ProcessTick();
    #endif

    plugin->processTick();
}
