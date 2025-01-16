// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#pragma once

#include <array>
#include <cstring>
#include <string>
#include <vector>
#include "amx.h"
#include "Value.hh"

namespace spsdk {

class AmxWrapper {
public:
    static void initialize(void* const* const ftable);
    static void shutdown();

    static AmxWrapper& getFromHandle(AMX* amx);

    int push(char const* string);
    int push(cell const* data, size_t length);
    int exec(cell& returnVal, cell index);
    int alloc(cell& amxAddr, cell*& physAddr, cell cellsCount);
    std::string loadString(cell amxAddr);
    int overwriteNative(std::string_view name, AMX_NATIVE newFn, AMX_NATIVE& previousFn);

    inline int release(cell amxAddr) {
        return amx_Release(m_handle, amxAddr);
    }

    inline int registerNatives(AMX_NATIVE_INFO* list, cell count) {
        return amx_Register(m_handle, list, count);
    }

    inline int findPublicFn(std::string_view name, cell& index) {
        return amx_FindPublic(m_handle, name.data(), &index);
    }

    inline AMX* handle() {
        return m_handle;
    }

    template<typename T>
    inline int push(T value) {
        static_assert(sizeof (T) <= sizeof (cell));
        static_assert(std::is_trivially_copyable_v<T>);

        return amx_Push(m_handle, *reinterpret_cast<cell*>(&value));
    }

    template<size_t S>
    inline int push(std::array<cell, S> const& array) {
        return push(array.data(), array.size());
    }

    template<typename T, typename... Args>
    inline int exec(T& returnVal, cell index, Args... args) {
        pushArgs(args...);

        cell rawReturnVal;

        if (int result = exec(rawReturnVal, index); result != AMX_ERR_NONE)
            return result;

        if constexpr (!std::is_void_v<T>) {
            static_assert(sizeof (T) <= sizeof (cell));
            static_assert(std::is_trivially_copyable_v<T>);

            returnVal = *reinterpret_cast<T*>(&rawReturnVal);
        }

        return AMX_ERR_NONE;
    }

    template<typename T>
    inline int exec(T& returnVal, cell index, std::vector<PawnValue> const& args) {
        for (auto it = args.rbegin(); it != args.rend(); ++it)
            it->push(*this);

        cell rawReturnVal;

        if (int result = exec(rawReturnVal, index); result != AMX_ERR_NONE)
            return result;

        if constexpr (!std::is_void_v<T>) {
            static_assert(sizeof (T) <= sizeof (cell));
            static_assert(std::is_trivially_copyable_v<T>);

            returnVal = *reinterpret_cast<T*>(&rawReturnVal);
        }

        return AMX_ERR_NONE;
    }

private:
    AmxWrapper(AMX* amx) : m_handle(amx) {}

    template<typename T>
    inline void pushArgs(T val) {
        push(val);
    }

    template<typename T, typename... Args>
    inline void pushArgs(T const& val, Args... args) {
        pushArgs(args...);
        push(val);
    }

    std::vector<cell> m_allocations;
    AMX* m_handle;
};

template<>
inline int AmxWrapper::push(PawnValue const& value) {
    return value.push(*this);
}

template<>
inline int AmxWrapper::push(std::string_view string) {
    return push(string.data());
}

template<>
inline int AmxWrapper::push(char* string) {
    return push(const_cast<char const*>(string));
}

} // namespace spsdk
