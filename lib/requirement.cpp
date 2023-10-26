//
// Created by Bogdan Petru on 26.10.2023.
//

#include "requirement.h"

namespace Sugar::CLI {
    requirement_t::requirement_t(const requirement_val_t& _value) {
        this->value = _value;
    }
}
