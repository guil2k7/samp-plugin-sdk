// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#pragma once

#include <cstddef>
#include <cstdint>
#include <utility>
#include "AmxUtils.hh"

namespace spsdk {

enum class PawnValueType {
    kUndefined,
    kUInt,
    kInt,
    kFloat,
    kString,
    kArray,
};

class PawnValue {
public:
    PawnValue() : type(PawnValueType::kUndefined) {}
    
    inline PawnValue(PawnValue&& that) {
        *this = std::move(that);
    }

    PawnValue(PawnValue const& that) = delete;

    ~PawnValue();

    PawnValue& operator =(PawnValue const& that) = delete;
    PawnValue& operator =(PawnValue&& that);

    int push(AmxAllocManager& allocManager) const;

    PawnValueType type;

    union {
        uint32_t u;
        int32_t i;
        float f;

        struct {
            char* data;
            size_t length;
        } string;

        struct {
            cell* data;
            size_t length;
        } array;
    } data;
};

} // namespace spsdk
