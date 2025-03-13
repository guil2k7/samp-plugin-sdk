// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#include <spsdk/Plugin.hh>
#include <spsdk/Logger.hh>
#include <sys/utsname.h>

using namespace spsdk;

class Example2 final : public IPlugin {
public:
    std::string getPluginName() const override {
        return "Uname";
    }

    bool init() override {
        Logger::global.logLnF(LogLevel::Info, "Plugin 'Example2' loaded.");
        Logger::global.logLnF(LogLevel::Info, "  Powered by spsdk.");

        utsname unameData;
        uname(&unameData);

        Logger::global.logLnF(LogLevel::Info, "nodename: %s", unameData.nodename);
        Logger::global.logLnF(LogLevel::Info, "release: %s", unameData.release);
        Logger::global.logLnF(LogLevel::Info, "version: %s", unameData.version);
        Logger::global.logLnF(LogLevel::Info, "machine: %s", unameData.machine);

        return true;
    }

    void free() override {
        delete this;
    }

    int onAmxLoaded(AMX* amx) override {
        return AMX_ERR_NONE;
    }

    virtual int onAmxUnload(AMX* amx) override {
        return AMX_ERR_NONE;
    }
};

SPSDK_GET_PLUGIN() {
    return new Example2();
}
