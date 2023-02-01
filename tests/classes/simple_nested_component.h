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
			 height("height", RequirementLevel::Required, "Height of the user"),
			 is_married("is_married",RequirementLevel::Optional, "Marriage status", std::nullopt, false)
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
			 name("name", RequirementLevel::Required, "Name of the user"),
			 age("age", RequirementLevel::Required,"Age of the user")
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
			 action("action", RequirementLevel::Required,"action",1)
	{
		register_item(action);
		child_component_switch = &action;
		register_child_component(std::make_shared<child_component>());
		register_child_component(std::make_shared<child_component2>());
	};
};
