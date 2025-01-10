// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#include <array>
#include <spsdk/Plugin.hh>
#include <spsdk/Logger.hh>
#include <spsdk/amx/amx.h>

using namespace spsdk;

static cell AMX_NATIVE_CALL native_HelloWorld(AMX* amx, cell* params) {
    LOGGER.logLnF(LOG_LEVEL_INFO, "Hello, world!");
    return 1;
}

class HelloWorld final : public IPlugin {
public:
    std::string getPluginName() const override {
        return "HelloWorld";
    }

    bool init() override {
        LOGGER.logLnF(LOG_LEVEL_INFO, "Plugin 'HelloWorld' loaded.");
        LOGGER.logLnF(LOG_LEVEL_INFO, "  Powered by spsdk.");

        return true;
    }

    void free() override {

    }

    int onAmxLoaded(AMX* amx) override {
        static std::array<AMX_NATIVE_INFO, 1> NATIVE_LIST = {
            { "HelloWorld", native_HelloWorld }
        };

        return amx_Register(amx, NATIVE_LIST.data(), NATIVE_LIST.size());
    }

    virtual int onAmxUnload(AMX* amx) override {
        return AMX_ERR_NONE;
    }
};

SPSDK_GET_PLUGIN() {
    return new HelloWorld();
}
