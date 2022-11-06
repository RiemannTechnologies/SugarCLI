#pragma once

#include <configuration_item.h>
#include <configurable_component_t.h>
#include <impl/parser_impl.h>
#include <gtest/gtest.h>
#include <memory>


class test_component : public riemann::configurable_component_t {
public:
    riemann::configuration_item<std::string> name;
    riemann::configuration_item<int> age;
    riemann::configuration_item<double> height;
    riemann::configuration_item<bool> is_married;
    riemann::configuration_item<char> favourite_letter;//idfk
    test_component() : configurable_component_t("test", "This is a test"),
                       name("name", "Name of the user", std::nullopt, riemann::RequirementLevel::Required),
                       age("age", "Age of the user", std::nullopt, riemann::RequirementLevel::Required),
                       height("height", "Height of the user", std::nullopt, riemann::RequirementLevel::Required),
                       is_married("is_married", "Whether the user is married or not", std::nullopt,
                                  riemann::RequirementLevel::Optional, false),
                       favourite_letter("favourite_letter", "Favourite letter, idfk", std::nullopt,
                                        riemann::RequirementLevel::Optional,
                                        'H') {
        register_item(name);
        register_item(age);
        register_item(height);
        register_item(is_married);
        register_item(favourite_letter);

    };
};
