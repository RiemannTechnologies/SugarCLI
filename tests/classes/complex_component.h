#pragma once

#include <configuration_item.h>
#include <configurable_component_t.h>
#include <impl/parser_impl.h>
#include <gtest/gtest.h>
#include <memory>
#include <iostream>
#include <configuration_option.h>

using namespace Sugar::CLI;
class complex_component : public configurable_component_t {
public:
	configuration_item<std::string> name = configuration_item<std::string>("name", RequirementLevel::Required, "Name of the user");
	configuration_item<int> age = configuration_item<int>("age", RequirementLevel::Required, "Age of the user");
	configuration_item<double> height = configuration_item<double>("height", RequirementLevel::Required, "Height of the user");
	configuration_item<bool> is_married = configuration_item<bool>("is_married", RequirementLevel::Optional, "Is the user married",std::nullopt,false) ;
	configuration_item<char> favourite_letter = configuration_item<char>("favourite_letter", RequirementLevel::Optional,
                                                                         "Favourite letter of the user",std::nullopt,'H');//idfk
	configuration_option help = configuration_option("help", "help", [this](auto context) {
        this->is_called = true;
    });

	bool is_called = false;

	explicit complex_component()
			: configurable_component_t("test", "This is a test")
	{
		register_item(name);
		register_item(age);
		register_item(height);
		register_item(is_married);
		register_item(favourite_letter);
		register_item(help);

	};
    virtual ~complex_component() = default;
};
