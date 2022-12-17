#pragma once

#include <map>
#include "configurable_component_t.h"
#include "impl/parser_impl.h"

namespace riemann {
    class parser {

        parser_impl m_parser;
    public:
        explicit parser(configurable_component_t *_cmp) : m_parser(_cmp, "MyProgram") {};//FIXME: DO NOT UNDER ANY CIRCUMSTANCES USE THIS HARD CODED VALUE IN PRODUCTION

        void start_parse(int argc, const char **argv) {
            m_parser.start_parse(argc, argv);
        };
    };
}