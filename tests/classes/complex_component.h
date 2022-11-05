#pragma once

#include "../../src/cli/configuration_item.h"
#include "../../src/cli/configurable_component_t.h"
#include "../../src/cli/impl/parser_impl.h"
#include <gtest/gtest.h>
#include <memory>
#include <iostream>


class complex_component : public riemann::configurable_component_t {
public:
    riemann::configuration_item<std::string> name;
    riemann::configuration_item<int> age;
    riemann::configuration_item<double> height;
    riemann::configuration_item<bool> is_married;
    riemann::configuration_item<char> favourite_letter;//idfk
    riemann::configuration_option help;

    bool is_called = false;

    complex_component() : configurable_component_t("test", "This is a test"),
                          name("name", "Name of the user", std::nullopt, riemann::RequirementLevel::Required),
                          age("age", "Age of the user", std::nullopt, riemann::RequirementLevel::Required),
                          height("height", "Height of the user", std::nullopt, riemann::RequirementLevel::Required),
                          is_married("is_married", "Whether they are married or not", std::nullopt,
                                     riemann::RequirementLevel::Optional, false),
                          favourite_letter("favourite_letter", "Their favourite letter idk", std::nullopt,
                                           riemann::RequirementLevel::Optional,
                                           'H'),
                          help("help", "help", [this](auto context) {
                              std::stringstream stringstream;
                              context.print(stringstream);
                              std::cout << stringstream.str();
                              this->is_called = true;
                          }) {
        register_item(name);
        register_item(age);
        register_item(height);
        register_item(is_married);
        register_item(favourite_letter);
        register_item(help);

    };
};
