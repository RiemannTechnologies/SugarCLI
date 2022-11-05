#pragma once

#include "../../src/cli/configuration_item.h"
#include "../../src/cli/configurable_component_t.h"
#include "../../src/cli/impl/parser_impl.h"
#include <gtest/gtest.h>
#include <memory>


class positional_component : public riemann::configurable_component_t {
public:

    riemann::configuration_item<std::string> name;
    riemann::configuration_item<int> age;
    riemann::configuration_item<std::vector<std::string>> intrests;

    positional_component() : configurable_component_t("test", "This is a test"),
                             name("name", "Name of the user", 1, riemann::RequirementLevel::Required),
                             age("age", "Age of the user", 1, riemann::RequirementLevel::Required),
                             intrests("things", "amogus", -1, riemann::RequirementLevel::Required) {
        register_item(name);
        register_item(age);
        register_item(intrests);

    };
};
