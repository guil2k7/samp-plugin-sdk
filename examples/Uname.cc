// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#include <spsdk/Plugin.hh>
#include <spsdk/Logger.hh>
#include <sys/utsname.h>

using namespace spsdk;

class UnamePlugin final : public IPlugin {
public:
    std::string getPluginName() const override {
        return "Uname";
    }

    bool init() override {
        LOGGER.logLnF(LOG_LEVEL_INFO, "Plugin 'UnamePlugin' loaded.");
        LOGGER.logLnF(LOG_LEVEL_INFO, "  Powered by spsdk.");

        utsname unameData;
        uname(&unameData);

        LOGGER.logLnF(LOG_LEVEL_INFO, "nodename: %s", unameData.nodename);
        LOGGER.logLnF(LOG_LEVEL_INFO, "release: %s", unameData.release);
        LOGGER.logLnF(LOG_LEVEL_INFO, "version: %s", unameData.version);
        LOGGER.logLnF(LOG_LEVEL_INFO, "machine: %s", unameData.machine);

        return true;
    }

    void free() override {

    }

    int onAmxLoaded(AmxWrapper& amx) override {
        return AMX_ERR_NONE;
    }

    virtual int onAmxUnload(AmxWrapper& amx) override {
        return AMX_ERR_NONE;
    }
};

SPSDK_GET_PLUGIN() {
    return new UnamePlugin();
}
