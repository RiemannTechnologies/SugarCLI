#pragma once
#include "component.h"
#include "internal/internal_parser.h"
#include "internal/string_convertor.h"
namespace Sugar::CLI {
    struct runner{
        component* main_component;
        runner(component* main) : main_component(main){}

        void parsing_phase(size_t argc, char **argv) const {
            auto item_list = main_component->advertise_items();

            internal_parser parser;
            string_convertor convertor;
            argv_t argv_strings = convertor.to_string_array(argc,argv);
            vmap map = parser.generate_vmap(argv_strings);
            for(auto& item : item_list)
            {
                item->parse(map);
            }
        }
        int run_phase()
        {
            return main_component->run();
        }
        int run_with_argc_argv(std::size_t argc, char** argv){
            parsing_phase(argc, argv);
            return run_phase();
        }


    };
}
