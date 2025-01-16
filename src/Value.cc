// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#include <spsdk/AmxWrapper.hh>
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

int PawnValue::push(AmxWrapper& amx) const {
    switch (type) {
    case PawnValueType::Int:
        return amx.push(data.i);

    case PawnValueType::Float:
        return amx.push(data.f);

    case PawnValueType::UInt:
        return amx.push(data.u);

    case PawnValueType::String:
        return amx.push(data.string.data);

    case PawnValueType::Array:
        return amx.push(data.array.data, data.array.length);

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
