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
        logger.logLnF(LOG_LEVEL_INFO, "Plugin 'UnamePlugin' loaded.");
        logger.logLnF(LOG_LEVEL_INFO, "  Powered by spsdk.");

        utsname unameData;
        uname(&unameData);

        logger.logLnF(LOG_LEVEL_INFO, "nodename: %s", unameData.nodename);
        logger.logLnF(LOG_LEVEL_INFO, "release: %s", unameData.release);
        logger.logLnF(LOG_LEVEL_INFO, "version: %s", unameData.version);
        logger.logLnF(LOG_LEVEL_INFO, "machine: %s", unameData.machine);

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
    return new UnamePlugin();
}
