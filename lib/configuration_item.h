#pragma once

#include <IOStreamable.h>
#include <Parser.h>
#include "item.h"

namespace Sugar::CLI {

    template<typename T> requires Input::IOStreamable<T>
    struct configuration_item : public item<T> {

        configuration_item(const std::string &name, const std::string &description, const requirement_val_t &requirement)
                : item<T>(name, description, requirement) {}

        virtual ~configuration_item() = default;

        [[nodiscard]] virtual std::vector<std::string_view> match_id() const{
            return {"--"+this->name, "-"+this->name[0]};
        }


        virtual bool matcher (const cli_environment& env){
            auto matches = match_id();

            for(int i = 0 ; i < env.arguments.size(); ++i)
            {
                auto& value = env.arguments[i];
                if(value == matches[0] || value == matches[1] && i<env.arguments.size()-1)
                {
                    try{
                        Input::Parser parser;
                        parser.Parse(this->value, matches[i+1]);
                        return true;
                    }
                    catch (std::invalid_argument& arg)
                    {
                        return false;
                    }
                }
            }
            return false;
        }
        virtual void success (){
            return;
        }
        virtual void fail (){
            return;
        }

    };
}