#pragma once
#include <IOStreamable.h>
#include <optional>
#include <iostream> //for istream and ostream

namespace Sugar::CLI {
    template <Input::IOStreamable T>
    struct error_handler_result{
        bool shouldTryAgain = false;
        std::optional<T> newValue = std::nullopt;

        error_handler_result(const std::optional<T> &newValue, bool shouldTryAgain) : shouldTryAgain(shouldTryAgain),
                                                                                      newValue(newValue) {}
    };

    template <Input::IOStreamable T>
    struct handling_procedure{
        virtual ~handling_procedure() = default;
        virtual error_handler_result<T> error() = 0;
    };
}
