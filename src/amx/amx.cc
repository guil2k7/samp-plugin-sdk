// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#include <spsdk/amx/amx.h>

void AMXAPI amx_InitLibrary(void* const* const ftable) {
    *reinterpret_cast<void** const>(&amx_Align16) = ftable[0];
    *reinterpret_cast<void** const>(&amx_Align32) = ftable[1];
    *reinterpret_cast<void** const>(&amx_Align64) = ftable[2];
    *reinterpret_cast<void** const>(&amx_Allot) = ftable[3];
    *reinterpret_cast<void** const>(&amx_Callback) = ftable[4];
    *reinterpret_cast<void** const>(&amx_Cleanup) = ftable[5];
    *reinterpret_cast<void** const>(&amx_Clone) = ftable[6];
    *reinterpret_cast<void** const>(&amx_Exec) = ftable[7];
    *reinterpret_cast<void** const>(&amx_FindNative) = ftable[8];
    *reinterpret_cast<void** const>(&amx_FindPublic) = ftable[9];
    *reinterpret_cast<void** const>(&amx_FindPubVar) = ftable[10];
    *reinterpret_cast<void** const>(&amx_FindTagId) = ftable[11];
    *reinterpret_cast<void** const>(&amx_Flags) = ftable[12];
    *reinterpret_cast<void** const>(&amx_GetAddr) = ftable[13];
    *reinterpret_cast<void** const>(&amx_GetNative) = ftable[14];
    *reinterpret_cast<void** const>(&amx_GetPublic) = ftable[15];
    *reinterpret_cast<void** const>(&amx_GetPubVar) = ftable[16];
    *reinterpret_cast<void** const>(&amx_GetString) = ftable[17];
    *reinterpret_cast<void** const>(&amx_GetTag) = ftable[18];
    *reinterpret_cast<void** const>(&amx_GetUserData) = ftable[19];
    *reinterpret_cast<void** const>(&amx_Init) = ftable[20];
    *reinterpret_cast<void** const>(&amx_InitJIT) = ftable[21];
    *reinterpret_cast<void** const>(&amx_MemInfo) = ftable[22];
    *reinterpret_cast<void** const>(&amx_NameLength) = ftable[23];
    *reinterpret_cast<void** const>(&amx_NativeInfo) = ftable[24];
    *reinterpret_cast<void** const>(&amx_NumNatives) = ftable[25];
    *reinterpret_cast<void** const>(&amx_NumPublics) = ftable[26];
    *reinterpret_cast<void** const>(&amx_NumPubVars) = ftable[27];
    *reinterpret_cast<void** const>(&amx_NumTags) = ftable[28];
    *reinterpret_cast<void** const>(&amx_Push) = ftable[29];
    *reinterpret_cast<void** const>(&amx_PushArray) = ftable[30];
    *reinterpret_cast<void** const>(&amx_PushString) = ftable[31];
    *reinterpret_cast<void** const>(&amx_RaiseError) = ftable[32];
    *reinterpret_cast<void** const>(&amx_Register) = ftable[33];
    *reinterpret_cast<void** const>(&amx_Release) = ftable[34];
    *reinterpret_cast<void** const>(&amx_SetCallback) = ftable[35];
    *reinterpret_cast<void** const>(&amx_SetDebugHook) = ftable[36];
    *reinterpret_cast<void** const>(&amx_SetString) = ftable[37];
    *reinterpret_cast<void** const>(&amx_SetUserData) = ftable[38];
    *reinterpret_cast<void** const>(&amx_StrLen) = ftable[39];
    *reinterpret_cast<void** const>(&amx_UTF8Check) = ftable[40];
    *reinterpret_cast<void** const>(&amx_UTF8Get) = ftable[41];
    *reinterpret_cast<void** const>(&amx_UTF8Len) = ftable[42];
    *reinterpret_cast<void** const>(&amx_UTF8Put) = ftable[43];
}

uint16_t * (AMXAPI* amx_Align16)(uint16_t *v) = nullptr;
uint32_t * (AMXAPI* amx_Align32)(uint32_t *v) = nullptr;
uint64_t * (AMXAPI* amx_Align64)(uint64_t *v) = nullptr;
int (AMXAPI* amx_Allot)(AMX *amx, int cells, cell *amx_addr, cell **phys_addr) = nullptr;
int (AMXAPI* amx_Callback)(AMX *amx, cell index, cell *result, cell *params) = nullptr;
int (AMXAPI* amx_Cleanup)(AMX *amx) = nullptr;
int (AMXAPI* amx_Clone)(AMX *amxClone, AMX *amxSource, void *data) = nullptr;
int (AMXAPI* amx_Exec)(AMX *amx, cell *retval, int index) = nullptr;
int (AMXAPI* amx_FindNative)(AMX *amx, const char *name, int *index) = nullptr;
int (AMXAPI* amx_FindPublic)(AMX *amx, const char *funcname, int *index) = nullptr;
int (AMXAPI* amx_FindPubVar)(AMX *amx, const char *varname, cell *amx_addr) = nullptr;
int (AMXAPI* amx_FindTagId)(AMX *amx, cell tag_id, char *tagname) = nullptr;
int (AMXAPI* amx_Flags)(AMX *amx,uint16_t *flags) = nullptr;
int (AMXAPI* amx_GetAddr)(AMX *amx,cell amx_addr,cell **phys_addr) = nullptr;
int (AMXAPI* amx_GetNative)(AMX *amx, int index, char *funcname) = nullptr;
int (AMXAPI* amx_GetPublic)(AMX *amx, int index, char *funcname) = nullptr;
int (AMXAPI* amx_GetPubVar)(AMX *amx, int index, char *varname, cell *amx_addr) = nullptr;
int (AMXAPI* amx_GetString)(char *dest,const cell *source, int use_wchar, size_t size) = nullptr;
int (AMXAPI* amx_GetTag)(AMX *amx, int index, char *tagname, cell *tag_id) = nullptr;
int (AMXAPI* amx_GetUserData)(AMX *amx, long tag, void **ptr) = nullptr;
int (AMXAPI* amx_Init)(AMX *amx, void *program) = nullptr;
int (AMXAPI* amx_InitJIT)(AMX *amx, void *reloc_table, void *native_code) = nullptr;
int (AMXAPI* amx_MemInfo)(AMX *amx, long *codesize, long *datasize, long *stackheap) = nullptr;
int (AMXAPI* amx_NameLength)(AMX *amx, int *length) = nullptr;
AMX_NATIVE_INFO * (AMXAPI* amx_NativeInfo)(const char *name, AMX_NATIVE func) = nullptr;
int (AMXAPI* amx_NumNatives)(AMX *amx, int *number) = nullptr;
int (AMXAPI* amx_NumPublics)(AMX *amx, int *number) = nullptr;
int (AMXAPI* amx_NumPubVars)(AMX *amx, int *number) = nullptr;
int (AMXAPI* amx_NumTags)(AMX *amx, int *number) = nullptr;
int (AMXAPI* amx_Push)(AMX *amx, cell value) = nullptr;
int (AMXAPI* amx_PushArray)(AMX *amx, cell *amx_addr, cell **phys_addr, const cell array[], int numcells) = nullptr;
int (AMXAPI* amx_PushString)(AMX *amx, cell *amx_addr, cell **phys_addr, const char *string, int pack, int use_wchar) = nullptr;
int (AMXAPI* amx_RaiseError)(AMX *amx, int error) = nullptr;
int (AMXAPI* amx_Register)(AMX *amx, const AMX_NATIVE_INFO *nativelist, int number) = nullptr;
int (AMXAPI* amx_Release)(AMX *amx, cell amx_addr) = nullptr;
int (AMXAPI* amx_SetCallback)(AMX *amx, AMX_CALLBACK callback) = nullptr;
int (AMXAPI* amx_SetDebugHook)(AMX *amx, AMX_DEBUG debug) = nullptr;
int (AMXAPI* amx_SetString)(cell *dest, const char *source, int pack, int use_wchar, size_t size) = nullptr;
int (AMXAPI* amx_SetUserData)(AMX *amx, long tag, void *ptr) = nullptr;
int (AMXAPI* amx_StrLen)(const cell *cstring, int *length) = nullptr;
int (AMXAPI* amx_UTF8Check)(const char *string, int *length) = nullptr;
int (AMXAPI* amx_UTF8Get)(const char *string, const char **endptr, cell *value) = nullptr;
int (AMXAPI* amx_UTF8Len)(const cell *cstr, int *length) = nullptr;
int (AMXAPI* amx_UTF8Put)(char *string, char **endptr, int maxchars, cell value) = nullptr;
