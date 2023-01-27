#pragma once

#include <configuration_item.h>
#include <configurable_component_t.h>
#include <impl/parser_impl.h>
#include <gtest/gtest.h>
#include <memory>

using namespace Sugar::CLI;
class child_component : public configurable_component_t {
public:
	configuration_item<double> height;
	configuration_item<bool> is_married;

	child_component()
			:configurable_component_t("first", "This is the first component"),
			 height("height", "Height of the user", std::nullopt, riemann::RequirementLevel::Required),
			 is_married("is_married", "Whether the user is married or not", std::nullopt,
					 riemann::RequirementLevel::Optional, false)
	{
		register_item(height);
		register_item(is_married);
	}
};

class child_component2 : public configurable_component_t {
public:
	configuration_item<std::string> name;
	configuration_item<int> age;

	child_component2()
			:configurable_component_t("second", "This is the second component"),
			 name("name", "Name of the user", std::nullopt, riemann::RequirementLevel::Required),
			 age("age", "Age of the user", std::nullopt, riemann::RequirementLevel::Required)
	{
		register_item(name);
		register_item(age);
	};
};

class nested_component : public configurable_component_t {
public:

	configuration_item<std::string> action;//idfk
	nested_component()
			:configurable_component_t("test", "This is a test"),
			 action("action", "", 1, riemann::RequirementLevel::Required)
	{
		register_item(action);
		child_component_switch = action.name;
		register_child_component(std::make_shared<child_component>());
		register_child_component(std::make_shared<child_component2>());
	};
};
