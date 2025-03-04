// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#include <spsdk/Utils.hh>
#include <spsdk/Logger.hh>

using namespace spsdk;

int AmxAllocManager::alloc(cell* amxAddr, cell** physAddr, cell cellCount) {
    int error = amx_Allot(amx, cellCount, amxAddr, physAddr);

    if (error != AMX_ERR_NONE) {
        logger.logLnF(LOG_LEVEL_CRITICAL, "could not allocate %d cells", cellCount);
        return error;
    }

    return AMX_ERR_NONE;
}

int AmxAllocManager::push(cell const* data, size_t length) {
    cell amxAddr;
    cell* physAddr;

    int error = amx_PushArray(amx, &amxAddr, &physAddr, data, length);

    if (error != AMX_ERR_NONE)
        return error;

    allocations.push_back(amxAddr);

    return AMX_ERR_NONE;
}

int AmxAllocManager::push(char const* string) {
    cell amxAddr;

    int error = amx_PushString(amx, &amxAddr, nullptr, string, 0, 0);

    if (error != AMX_ERR_NONE)
        return error;

    allocations.push_back(amxAddr);

    return AMX_ERR_NONE;
}

void AmxAllocManager::freeAll() {
    if (allocations.size() == 0)
        return;

    for (auto addr : allocations)
        amx_Release(amx, addr);

    allocations.clear();
}

std::string spsdk::amxLoadString(AMX* amx, cell amxAddr) {
    cell* physAddr;
    amx_GetAddr(amx, amxAddr, &physAddr);

    cell stringLen;
    amx_StrLen(physAddr, &stringLen);

    std::string string;
    string.resize(stringLen);

    amx_GetString(string.data(), physAddr, 0, stringLen + 1);

    return string;
}

int spsdk::amxOverwriteNative(AMX* amx, std::string_view name, AMX_NATIVE newFn, AMX_NATIVE& previousFn) {
    AMX_HEADER* hdr = reinterpret_cast<AMX_HEADER*>(amx->base);
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
        amx->flags |= AMX_FLAG_NTVREG;
        return AMX_ERR_NONE;
    }

    return AMX_ERR_NOTFOUND;
}
