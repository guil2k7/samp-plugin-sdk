// Copyright 2025 Maicol Castro (maicolcastro.abc@gmail.com).
// Distributed under the MIT License.
// See LICENSE.txt in the root directory of this project
// or at https://opensource.org/license/mit.

#include <spsdk/Value.hh>

using namespace spsdk;

PawnValue::~PawnValue() {
    switch (type) {
        case PawnValueType::kUndefined:
            break;

        case PawnValueType::kInt:
        case PawnValueType::kFloat:
        case PawnValueType::kUInt:
            break;

        case PawnValueType::kString:
            delete[] data.string.data;
            break;

        case PawnValueType::kArray:
            delete[] data.array.data;
            break;
    }
}

int PawnValue::push(AmxAllocManager& allocManager) const {
    switch (type) {
        case PawnValueType::kInt:
        case PawnValueType::kFloat:
        case PawnValueType::kUInt:
            return allocManager.push(data.i);

        case PawnValueType::kString:
            return allocManager.push(data.string.data);

        case PawnValueType::kArray:
            return allocManager.push(data.array.data, data.array.length);

        case PawnValueType::kUndefined:
            return AMX_ERR_NONE;
    }
}

PawnValue& PawnValue::operator =(PawnValue&& that) {
    type = that.type;

    switch (type) {
        case PawnValueType::kInt:
        case PawnValueType::kFloat:
        case PawnValueType::kUInt:
            data.i = that.data.i;
            break;

        case PawnValueType::kString:
            data.string = that.data.string;
            break;

        case PawnValueType::kArray:
            data.array = that.data.array;
            break;

        case PawnValueType::kUndefined:
            break;
    }

    that.type = PawnValueType::kUndefined;

    return *this;
}
