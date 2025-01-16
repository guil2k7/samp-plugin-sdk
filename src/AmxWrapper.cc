// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#include <unordered_map>
#include <spsdk/AmxWrapper.hh>
#include <spsdk/Logger.hh>

using namespace spsdk;

// From `amx.cc`.
void amx_InitLibrary(void* const* const ftable);

static std::unordered_map<AMX*, AmxWrapper*> AMX_INSTANCES;

void AmxWrapper::initialize(void* const* const ftable) {
    amx_InitLibrary(ftable);

    for (auto it : AMX_INSTANCES)
        delete it.second;

    AMX_INSTANCES.clear();
}

void AmxWrapper::shutdown() {
    for (auto it : AMX_INSTANCES)
        delete it.second;

    AMX_INSTANCES.clear();
}

AmxWrapper& AmxWrapper::getFromHandle(AMX* amx) {
    auto it = AMX_INSTANCES.find(amx);

    if (it == AMX_INSTANCES.end())
        it = AMX_INSTANCES.insert({amx, new AmxWrapper(amx)}).first;

    return *it->second;
}

int AmxWrapper::push(char const* string) {
    cell amxAddr;

    int error = amx_PushString(m_handle, &amxAddr, nullptr, string, 0, 0);

    if (error != AMX_ERR_NONE)
        return error;

    m_allocations.push_back(amxAddr);

    return AMX_ERR_NONE;
}

int AmxWrapper::push(cell const* data, size_t length) {
    cell amxAddr;
    cell* physAddr;

    int error = amx_PushArray(m_handle, &amxAddr, &physAddr, data, length);

    if (error != AMX_ERR_NONE)
        return error;

    m_allocations.push_back(amxAddr);

    return AMX_ERR_NONE;
}

int AmxWrapper::exec(cell& returnVal, cell index) {
    int error = amx_Exec(m_handle, &returnVal, index);

    if (error != AMX_ERR_NONE)
        return error;

    for (auto addr : m_allocations)
        amx_Release(m_handle, addr);

    m_allocations.clear();

    return AMX_ERR_NONE;
}

int AmxWrapper::alloc(cell& amxAddr, cell*& physAddr, cell cellsCount) {
    int error = amx_Allot(m_handle, cellsCount, &amxAddr, &physAddr);

    if (error != AMX_ERR_NONE) {
        LOGGER.logLnF(LOG_LEVEL_CRITICAL, "could not allocate %d cells", cellsCount);
        return error;
    }

    return AMX_ERR_NONE;
}

std::string AmxWrapper::loadString(cell amxAddr) {
    cell* physAddr;
    amx_GetAddr(m_handle, amxAddr, &physAddr);

    cell stringLen;
    amx_StrLen(physAddr, &stringLen);

    std::string string;
    string.resize(stringLen);

    amx_GetString(string.data(), physAddr, 0, stringLen + 1);

    return string;
}

int AmxWrapper::overwriteNative(std::string_view name, AMX_NATIVE newFn, AMX_NATIVE& previousFn) {
    AMX_HEADER* hdr = reinterpret_cast<AMX_HEADER*>(m_handle->base);
    AMX_FUNCPART* func = GETENTRY(hdr, natives, 0);

    bool found = false;
    size_t nativesCount = NUMENTRIES(hdr, natives, libraries);

    for (size_t i = 0; i < nativesCount; ++i) {
        if (name != GETENTRYNAME(hdr, func)) {
            func = reinterpret_cast<AMX_FUNCPART*>(
                reinterpret_cast<uint8_t*>(func) + hdr->defsize);

            continue;
        }

        previousFn = reinterpret_cast<AMX_NATIVE>(func->address);
        func->address = reinterpret_cast<ucell>(newFn);

        found = true;
        break;
    }

    if (found) {
        m_handle->flags |= AMX_FLAG_NTVREG;
        return AMX_ERR_NONE;
    }

    return AMX_ERR_NOTFOUND;
}
