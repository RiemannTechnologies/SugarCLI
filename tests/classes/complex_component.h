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
	configuration_item<std::string> name;
	configuration_item<int> age;
	configuration_item<double> height;
	configuration_item<bool> is_married;
	configuration_item<char> favourite_letter;//idfk
	configuration_option help;

	bool is_called = false;

	explicit complex_component()
			:configurable_component_t("test", "This is a test"),
			 name("name", RequirementLevel::Required, "Name of the user"),
			 age("age", RequirementLevel::Required, "Age of the user"),
			 height("height", RequirementLevel::Required, "Height of the user"),
			 is_married("is_married", RequirementLevel::Optional, "Is the user married", false),
			 favourite_letter("favourite_letter", RequirementLevel::Optional,
					 "Favourite letter of the user", 'H'),
			 help("help", "help", [this](auto context) {
			   this->is_called = true;
			 })
	{
		register_item(name);
		register_item(age);
		register_item(height);
		register_item(is_married);
		register_item(favourite_letter);
		register_item(help);

	};
};
