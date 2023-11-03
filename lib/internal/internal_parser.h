#pragma once
#include <map>
#include <string>
#include <vector>
#include "internal_vector_iterator.h"

namespace Sugar::CLI {
    using vmap = std::map<std::string, std::vector<std::string>,std::less<>>;
    using argv_t = std::vector<std::string>;
    struct internal_parser {
        static void handle_argument_header(
                vmap &result,
                internal_vector_iterator &iterator
        ) noexcept
        {
            result[iterator.value()] = std::vector<std::string>();
            if(iterator.can_continue())//we are not at the end
            {
                result[iterator.value()].emplace_back(iterator.next().value());
            }

        }
        static vmap generate_vmap(argv_t arguments)
        {
            vmap result;
            std::size_t n = arguments.size();
            if(n<=1) return result;

            internal_vector_iterator iterator(arguments);
            while(iterator.can_continue())
            {
                if(iterator.value().starts_with("--"))
                {
                    handle_argument_header(result,iterator);
                }
                iterator = iterator.next();
            }
            return result;
        }
    };
}