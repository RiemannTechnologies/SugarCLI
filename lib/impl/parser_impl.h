#pragma once

#include <memory>
#include "../configurable_component_t.h"
#include "../configuration_item.h"
#include "../interactive_item.h"
#include <stdexcept>
#include <iostream>
#include <CLI/cli.hpp>

namespace Sugar::CLI {

    enum class parse_result {
        MustBreak,
        CanContinue
    };

    class parser_impl {
    public:
        std::string pname;
        //We'll store all our available components into a so-called "keychain" for reference
        configurable_component_t *main;


        std::vector<std::string> raw_arguments;
        ArgumentDatabase database;

        std::istream *m_input = &std::cin;
        std::ostream *m_output = &std::cout;

        /**
         * INTERNAL ONLY - creates a new parser
         * @param _cmp component tree to be parsed
         */
        explicit parser_impl(configurable_component_t *_cmp) : main(_cmp){}

        void start_parse(int argc, const char **argv);

        void obtain_argument_data_recursive(configurable_component_t *component);


    };

}