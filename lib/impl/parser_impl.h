#pragma once

#include <memory>
#include "../configurable_component_t.h"
#include "../configuration_item.h"
#include "../interactive_item.h"
#include "../exception/cli_argument_not_found.h"
#include "../exception/module_not_found.h"
#include <stdexcept>
#include <iostream>

namespace riemann {

    enum class parse_result {
        MustBreak,
        CanContinue
    };

    class parser_impl {
    public:
        int argc;
        const char **argv;
        std::string pname;
        //We'll store all our available components into a so-called "keychain" for reference
        configurable_component_t *main;

        //variable maps and things
        cxxopts::ParseResult vm;
        cxxopts::Options od;
        std::vector<std::string> pod;


        std::istream *m_input = &std::cin;
        std::ostream *m_output = &std::cout;

        /**
         * INTERNAL ONLY - creates a new parser
         * @param _cmp component tree to be parsed
         */
        explicit parser_impl(configurable_component_t *_cmp, std::string programName="My Program") : main(_cmp), od(std::move(programName)){}

        //parse one component
        parse_result parse_component(configurable_component_t *component);

        void start_parse(int argc, const char **argv);

        void build_od(configurable_component_t *component);

        void main_parse_recursive_loop(configurable_component_t *component);
    };

}