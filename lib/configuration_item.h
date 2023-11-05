//
// Created by thonkdifferent on 05.11.2023.
//

#pragma once
#include "SugarInput/lib/IOStreamable.h"
#include "item.h"
#include "internal/default_parsing_strategy.h"
#include "internal/interactive_handling_procedure.h"
namespace Sugar::CLI {
    template<Input::IOStreamable T>
    struct configuration_item : public item<T>
    {
        explicit configuration_item(const std::string &name) : item<T>(name) {
            this->parsingStrategy = new default_parsing_strategy<T>;
            this->errorHandler = new interactive_handling_procedure<T>(name);
        }
        ~configuration_item(){
            delete this->parsingStrategy;
            delete this->errorHandler;
        }
    };
}
