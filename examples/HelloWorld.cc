// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#include <spsdk/Plugin.hh>
#include <spsdk/Logger.hh>

using namespace spsdk;

static cell AMX_NATIVE_CALL native_HelloWorld(AMX* amx, cell* params) {
    Logger::global.logLnF(LogLevel::Info, "Hello, world!");
    return 1;
}

class Example1 final : public IPlugin {
public:
    std::string getPluginName() const override {
        return "Example1";
    }

    bool init() override {
        Logger::global.logLnF(LogLevel::Info, "Plugin 'Example1' loaded.");
        Logger::global.logLnF(LogLevel::Info, "  Powered by spsdk.");

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
    return new Example1();
}
