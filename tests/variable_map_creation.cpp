#include <gtest/gtest.h>
#include "internal/type_definitions.h"
#include <internal/internal_parser.h>


namespace Sugar::CLI {
    TEST(variable_map_creation, from_name_and_age) {
        argv_t args = {"./myApp", "--name", "John", "--age", "25", "--height", "1.65"};

        internal_parser parser;
        vmap map = parser.generate_vmap(args);

        vmap result;
        result["--name"] = {"John"};
        result["--age"] = {"25"};
        result["--height"] = {"1.65"};

        ASSERT_EQ(map, result);
    }

    TEST(variable_map_creation, return_blank_if_no_argument_provided) {
        argv_t args = {"./myApp"};

        vmap result;
        internal_parser parser;
        vmap map = parser.generate_vmap(args);

        ASSERT_EQ(result, map);
    }
}