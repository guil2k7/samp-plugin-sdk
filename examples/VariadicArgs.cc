// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#include <spsdk/Plugin.hh>
#include <spsdk/VariadicArgs.hh>
#include <spsdk/Logger.hh>

using namespace spsdk;

/// # Example
/// ```pawn
/// native Callback:CreateCallback(const function[], const argsType[], {Float,_}:...);
/// native InvokeCallback(Callback:callback);
/// native DestroyCallback(Callback:callback);
///
/// forward Foobar(a, b, Float:c, d[]);
/// public Foobar(a, b, Float:c, d[]) {
///     printf("a: %d", a);
///     printf("b: %d", b);
///     printf("c: %f", c);
///     printf("d: %s", d);
///     printf("--------------------------------");
/// }
///
/// main() {
///     new Callback:callback1 = CreateCallback("Foobar", "iifs", 1, 2, 123.5, "Hello, world!");
///     new Callback:callback2 = CreateCallback("Foobar", "iifs", 5, 6, 567.89, "Hello, world!");
///
///     InvokeCallback(callback1);
///     InvokeCallback(callback1);
///
///     InvokeCallback(callback2);
///     InvokeCallback(callback2);
///
///     DestroyCallback(callback1);
///     DestroyCallback(callback2);
/// }
/// ```

struct Callback {
    AMX* amx;
    int fnIndex;
    std::vector<PawnValue> args;
};

// native Callback:CreateCallback(const function[], const argsType[], {Float,_}:...);
static cell AMX_NATIVE_CALL native_CreateCallback(AMX* amx, cell* params) {
    std::string fnName = amxLoadString(amx, params[1]);
    int fnIndex;

    if (amx_FindPublic(amx, fnName.c_str(), &fnIndex) != AMX_ERR_NONE) {
        logger.logLnF(LOG_LEVEL_WARNING, "function not found: %s", fnName.c_str());
        return 0;
    }

    std::vector<PawnValue> args;

    if (parseVariadicArgs(amx, params, 2, 3, args) != VariadicArgsParseError::kNone) {
        logger.logLnF(LOG_LEVEL_WARNING, "arguments parse error");
        return 0;
    }

    Callback* callback = new Callback();
    callback->amx = amx;
    callback->fnIndex = fnIndex;
    callback->args = std::move(args);

    return reinterpret_cast<cell>(callback);
}

// native InvokeCallback(Callback:callback);
static cell AMX_NATIVE_CALL native_InvokeCallback(AMX* amx, cell* params) {
    Callback* callback = reinterpret_cast<Callback*>(params[1]);

    AmxAllocManager allocManager(callback->amx);

    for (auto it = callback->args.rbegin(); it != callback->args.rend(); ++it)
        it->push(allocManager);

    cell retVal;
    amx_Exec(amx, &retVal, callback->fnIndex);

    return retVal;
}

// native DestroyCallback(Callback:callback);
static cell AMX_NATIVE_CALL native_DestroyCallback(AMX* amx, cell* params) {
    delete reinterpret_cast<Callback*>(params[1]);
    return 1;
}

class Example3 final : public IPlugin {
public:
    std::string getPluginName() const override {
        return "Example3";
    }

    bool init() override {
        logger.logLnF(LOG_LEVEL_INFO, "Plugin 'Example3' loaded.");
        logger.logLnF(LOG_LEVEL_INFO, "  Powered by spsdk.");

        return true;
    }

    void free() override {
        delete this;
    }

    int onAmxLoaded(AMX* amx) override {
        static AMX_NATIVE_INFO kNativeList[] = {
            { "CreateCallback", native_CreateCallback },
            { "InvokeCallback", native_InvokeCallback },
            { "DestroyCallback", native_DestroyCallback },
            { nullptr, nullptr }
        };

        return amx_Register(amx, kNativeList, -1);
    }

    virtual int onAmxUnload(AMX* amx) override {
        return AMX_ERR_NONE;
    }
};

SPSDK_GET_PLUGIN() {
    return new Example3();
}
