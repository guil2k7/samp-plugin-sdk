// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#include <spsdk/Plugin.hh>
#include <spsdk/Logger.hh>

using namespace spsdk;

static cell AMX_NATIVE_CALL native_HelloWorld(AMX* amx, cell* params) {
    logger.logLnF(LOG_LEVEL_INFO, "Hello, world!");
    return 1;
}

class HelloWorld final : public IPlugin {
public:
    std::string getPluginName() const override {
        return "HelloWorld";
    }

    bool init() override {
        logger.logLnF(LOG_LEVEL_INFO, "Plugin 'HelloWorld' loaded.");
        logger.logLnF(LOG_LEVEL_INFO, "  Powered by spsdk.");

        return true;
    }

    void free() override {
        delete this;
    }

    int onAmxLoaded(AMX* amx) override {
        static AMX_NATIVE_INFO kNativeList[] = {
            { "HelloWorld", native_HelloWorld },
            { nullptr, nullptr }
        };

        return amx_Register(amx, kNativeList, -1);
    }

    virtual int onAmxUnload(AMX* amx) override {
        return AMX_ERR_NONE;
    }
};

SPSDK_GET_PLUGIN() {
    return new HelloWorld();
}
