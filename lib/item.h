#pragma once
#include <IOStreamable.h>
#include <memory>
#include "internal/handling_procedure.h"
#include "internal/parsing_strategy.h"
namespace Sugar::CLI {

    template <Input::IOStreamable T>
    struct item{
        T value;
        std::string arg_name;
        handling_procedure<T>* errorHandler;
        parsing_strategy<T>* parsingStrategy;

        virtual ~item() = default;
        void parse(const vmap& map)
        {
            auto result = parsingStrategy->parse(arg_name, map);

            if(result!=std::nullopt)
            {
                value = result.value();
                return;
            }

            error_handler_result<T> eHandlerRes = errorHandler->error();
            while(eHandlerRes.shouldTryAgain)
            {
                eHandlerRes = errorHandler->error();
            }

            if(eHandlerRes.newValue == std::nullopt) return;
            value = eHandlerRes.newValue.value();
        }
        explicit item(const std::string& name): arg_name("--"+name){}
    };
}
