#pragma once
#include "handling_procedure.h"
#include <IOStreamReader.h>
#include <IOException.h>

#include <utility>
namespace Sugar::CLI {
    template <Input::IOStreamable T>
    struct interactive_handling_procedure : public handling_procedure<T>
    {
        ~interactive_handling_procedure() = default;
        std::istream* input_stream = &std::cin;
        std::ostream* output_stream = &std::cout;

        std::string message;

        explicit interactive_handling_procedure(const std::string& value_name, std::string custom_message="")
        {
            if(custom_message.empty())
                message = "Please type in the value for \""+value_name+"\": ";
            else
                message = std::move(custom_message)+": ";
        }



        error_handler_result<T> error() override {
            *output_stream<<message;
            Input::IOStreamReader reader(*input_stream);

            std::optional <T> newVal = std::nullopt;
            bool shouldTryAgain = false;
            try{
                newVal = reader.Read<T>();
            }
            catch (std::exception& exception) {
                shouldTryAgain = true;
                *output_stream<<"Invalid input. Try again\n";
            }
            return {newVal,shouldTryAgain};
        }
    };
}
