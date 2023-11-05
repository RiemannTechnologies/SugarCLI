#include <gtest/gtest.h>
//#include <gmock/gmock.h>
#include <optional>
#include "internal/type_definitions.h"
#include "internal/default_parsing_strategy.h"

namespace Sugar::CLI{

    TEST(item_parsing, accept_string_value)
    {

        default_parsing_strategy<std::string> strategy;
        vmap testMap;
        testMap["--testArg"] = {"Success"};
        std::optional<std::string> result = strategy.parse("--testArg", testMap);
        ASSERT_NE(result, std::nullopt);
        std::string unwrapped = result.value();
        ASSERT_EQ(unwrapped,"Success");


    }
    TEST(item_parsing, accept_integer_value)
    {
        default_parsing_strategy<int> strategy;
        vmap testMap;
        testMap["--testArg"] = {"12"};
        std::optional<int> result = strategy.parse("--testArg", testMap);
        ASSERT_NE(result, std::nullopt);
        int unwrapped = result.value();
        ASSERT_EQ(unwrapped,12);
    }
    TEST(item_parsing, accept_floating_point_value)
    {
        default_parsing_strategy<double> strategy;
        vmap testMap;
        testMap["--testArg"] = {"1.65"};
        std::optional<double> result = strategy.parse("--testArg", testMap);
        ASSERT_NE(result, std::nullopt);
        double unwrapped = result.value();
        ASSERT_EQ(unwrapped,1.65);
    }
    TEST(item_failiure, return_null_when_required_value_is_not_found)
    {
        default_parsing_strategy<std::string> strategy;
        vmap testMap;
        testMap["--testArg"] = {"Success"};
        std::optional<std::string> result = "ERROR";
        ASSERT_NO_THROW(result = strategy.parse("--anotherTestArg", testMap));
        ASSERT_EQ(result, std::nullopt);
    }
    TEST(item_failiure, return_null_when_int_is_mallformed)
    {
        default_parsing_strategy<int> strategy;
        vmap testMap;
        testMap["--testArg"] = {"ERROR"};
        std::optional<int> result = 500;
        ASSERT_NO_THROW(result = strategy.parse("--anotherTestArg", testMap));
        ASSERT_EQ(result, std::nullopt);
    }
    TEST(item_failiure, return_null_when_float_is_given_to_int_field)
    {
        default_parsing_strategy<int> strategy;
        vmap testMap;
        testMap["--testArg"] = {"4.20"};
        std::optional<int> result = 500;
        ASSERT_NO_THROW(result = strategy.parse("--testArg", testMap));
        ASSERT_EQ(result, std::nullopt);
    }
    TEST(item_failiure, return_null_when_float_is_mallformed)
    {
        default_parsing_strategy<float> strategy;
        vmap testMap;
        testMap["--testArg"] = {"ERROR"};
        std::optional<float> result = 500;
        ASSERT_NO_THROW(result = strategy.parse("--testArg", testMap));
        ASSERT_EQ(result, std::nullopt);
    }

}