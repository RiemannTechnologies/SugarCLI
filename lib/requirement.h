#pragma once

namespace Sugar::CLI {
    enum class requirement_val_t {
        Optional,
        Required
    };

    struct requirement_t {
        requirement_val_t value;
        explicit requirement_t(const requirement_val_t &_value);
    };
};