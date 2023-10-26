#pragma once
#include <configuration_item.h>
#include <configurable_component_t.h>
#include <impl/parser_impl.h>
#include "util/strutil.hpp"
#include <gtest/gtest.h>
#include <IOStreamable.h>
#include <memory>
#include <iostream>
#include <gmock/gmock.h>

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

template <Sugar::Input::IOStreamable T>
class mock_interactive_item : public interactive_item<T>
{
public:
    MOCK_METHOD(void, handle_invalid_args, (), (override));
    explicit mock_interactive_item(
            std::string name,
            std::string input_text,
            RequirementLevel level,
            std::string help_text
    ) : interactive_item<T>(name,input_text,level,help_text)
            {};
};
class interactive_component : public configurable_component_t {
public:
	mock_interactive_item<std::string> name;
	mock_interactive_item<int> age;
	mock_interactive_item<double> height;
	configuration_item<bool> is_married;
	configuration_item<char> favourite_letter;//idfk

    void set_io_for_components(std::istream* input, std::ostream* output)
    {
        name.m_input = input;
        age.m_input = input;
        height.m_input = input;

        name.m_output = output;
        age.m_output = output;
        height.m_output = output;
    }
	interactive_component()
			:configurable_component_t("test", "This is a test"),
			 name("name", "Please input your name", RequirementLevel::Required, "Name of the user"),
			 age("age", "Please input your age", RequirementLevel::Required,"Age of the user"),
			 height("height","Please input your height",RequirementLevel::Required, "Height of the user"),
			 is_married("is_married", RequirementLevel::Optional, "Whether the user is married or not"),
			 favourite_letter("favourite_letter",RequirementLevel::Optional, "Favourite letter, idfk")
	{



		register_item(name);
		register_item(age);
		register_item(height);
		register_item(is_married);
		register_item(favourite_letter);
	};
};
