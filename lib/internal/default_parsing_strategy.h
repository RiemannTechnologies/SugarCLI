#pragma once
#include "parsing_strategy.h"
#include <Parser.h>
namespace Sugar::CLI{
    template <Input::IOStreamable T>
    struct default_parsing_strategy : public parsing_strategy<T> {
        std::optional<T> parse(const std::string &lookupArgument, const vmap &varMap) noexcept override {
            Input::Parser parser;
            T result;
            if(!varMap.contains(lookupArgument)) return {};
            try {
                parser.Parse(result, varMap.at(lookupArgument)[0]);
            }
            catch (std::exception& e)
            {
                return {};
            }
            return result;
        }

        ~default_parsing_strategy() = default;
    };
}