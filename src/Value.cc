// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#include <spsdk/Value.hh>

using namespace spsdk;

PawnValue::~PawnValue() {
    switch (type) {
        case PawnValueType::Undefined:
            break;

        case PawnValueType::Int:
        case PawnValueType::Float:
        case PawnValueType::UInt:
            break;

        case PawnValueType::String:
            delete[] data.string.data;
            break;

        case PawnValueType::Array:
            delete[] data.array.data;
            break;
    }
}

int PawnValue::push(AmxAllocManager& allocManager) const {
    switch (type) {
        case PawnValueType::Int:
        case PawnValueType::Float:
        case PawnValueType::UInt:
            return allocManager.push(data.i);

        case PawnValueType::String:
            return allocManager.push(data.string.data);

        case PawnValueType::Array:
            return allocManager.push(data.array.data, data.array.length);

        case PawnValueType::Undefined:
            return AMX_ERR_NONE;
    }
}

PawnValue& PawnValue::operator =(PawnValue&& that) {
    type = that.type;

    switch (type) {
        case PawnValueType::Int:
        case PawnValueType::Float:
        case PawnValueType::UInt:
            data.i = that.data.i;
            break;

        case PawnValueType::String:
            data.string = that.data.string;
            break;

        case PawnValueType::Array:
            data.array = that.data.array;
            break;

        case PawnValueType::Undefined:
            break;
    }

    that.type = PawnValueType::Undefined;

    return *this;
}
