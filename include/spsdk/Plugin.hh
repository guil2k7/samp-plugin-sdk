// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#pragma once

#include "amx/amx.h"
#include <string>

namespace spsdk {

enum PluginFlag {
    PLUGIN_FLAG_PROCESS_TICK = 1 << 1,
};

static constexpr int PLUGIN_DEFAULT_FLAGS = 0;

class IPlugin {
public:
    virtual int getFlags() const {
        return PLUGIN_DEFAULT_FLAGS;
    }

    virtual std::string getPluginName() const = 0;

    virtual bool init() = 0;
    virtual void free() = 0;

    virtual int onAmxLoaded(AMX* amx) = 0;
    virtual int onAmxUnload(AMX* amx) = 0;

    virtual void processTick() {}
};

#define SPSDK_GET_PLUGIN() \
extern "C" spsdk::IPlugin* _spsdk_getPlugin()

} // namespace spsdk
