// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#pragma once

#include <vector>
#include "Value.hh"

namespace spsdk {

enum class VariadicArgsParseError {
    None,
    ArgsCountMismatch,
    InvalidSpecifierUse,
    UnknownSpecifier,
};

VariadicArgsParseError parseVariadicArgs(AMX* amx, cell const* args, size_t formatIndex, size_t vargsIndex, std::vector<PawnValue>& output);

} // namespace spsdk
