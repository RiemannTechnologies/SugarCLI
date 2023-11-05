#pragma once
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <internal/handling_procedure.h>
#include <internal/parsing_strategy.h>
#include <IOStreamable.h>
#include "item.h"

namespace Sugar::CLI {
    template <Input::IOStreamable T>
    struct mock_parsing_strategy : public parsing_strategy<T>{
        MOCK_METHOD(std::optional<T>, parse, (const std::string &lookupArgument, const vmap &varMap), (noexcept));
    };

    template <Input::IOStreamable T>
    struct mock_error_handling_strategy : public handling_procedure<T>{
        MOCK_METHOD(error_handler_result<T>, error, ());
    };

}
