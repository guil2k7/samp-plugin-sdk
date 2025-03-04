// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#pragma once

#include <string>
#include <vector>
#include "amx.h"

namespace spsdk {

class AmxAllocManager {
public:
    AmxAllocManager(AMX* amx = nullptr) : amx{amx} {}

    inline ~AmxAllocManager() {
        freeAll();
    }

    int alloc(cell* amxAddr, cell** physAddr, cell cellCount);

    template<typename T>
    inline int push(T value) {
        static_assert(sizeof(T) <= sizeof(cell));
        static_assert(std::is_trivially_copyable_v<T>);
        static_assert(!std::is_pointer_v<T>);

        return amx_Push(amx, *reinterpret_cast<cell*>(&value));
    }

    int push(cell const* data, size_t length);
    int push(char const* string);

    void freeAll();

    AMX* amx;
    std::vector<cell> allocations;
};

template<>
inline int AmxAllocManager::push(char* string) {
    return push(const_cast<char const*>(string));
}

std::string amxLoadString(AMX* amx, cell amxAddr);
int amxOverwriteNative(AMX* amx, std::string_view name, AMX_NATIVE newFn, AMX_NATIVE& previousFn);

} // namespace spsdk
