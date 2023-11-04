#pragma once
#include <optional>
#include "type_definitions.h"
#include <IOStreamable.h>
namespace Sugar::CLI{

    template <Input::IOStreamable T>
    struct parsing_strategy{
        virtual std::optional<T> parse(const std::string &lookupArgument, const vmap &varMap) noexcept = 0;
        virtual ~parsing_strategy() = default;
    };
}