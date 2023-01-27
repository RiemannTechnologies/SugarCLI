#pragma once
#include <configuration_item.h>
#include <configurable_component_t.h>
#include <impl/parser_impl.h>
#include "util/strutil.hpp"
#include <gtest/gtest.h>
#include <memory>
#include <iostream>

using namespace Sugar::CLI;
std::string place_on_new_lines(const std::string& input)
{
	auto components = split(input, ' ');
	std::string output;
	for (auto& item : components) {
		output += item += '\n';
	}
	return output;
}
class interactive_component : public configurable_component_t {
public:
	interactive_item<std::string> name;
	interactive_item<int> age;
	interactive_item<double> height;
	configuration_item<bool> is_married;
	configuration_item<char> favourite_letter;//idfk

	interactive_component()
			:configurable_component_t("test", "This is a test"),
			 name("name", "Please input your name", Sugar::CLI::RequirementLevel::Required, "Name of the user"),
			 age("age", "Age of the user", "Please input your age", std::nullopt),
			 height("height", "Height of the user", "Please input your height", std::nullopt),
			 is_married("is_married", "Whether the user is married or not", std::nullopt,
					 RequirementLevel::Optional, false),
			 favourite_letter("favourite_letter", "Favourite letter, idfk", std::nullopt,
					 RequirementLevel::Optional,
					 'H')
	{
		register_item(name);
		register_item(age);
		register_item(height);
		register_item(is_married);
		register_item(favourite_letter);

	};
};
