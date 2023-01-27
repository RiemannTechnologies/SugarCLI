#pragma once
#include <configuration_item.h>
#include <configurable_component_t.h>
#include <impl/parser_impl.h>
#include <gtest/gtest.h>
#include <memory>

using namespace Sugar::CLI;
class component_with_arrays : public configurable_component_t {
public:
	configuration_item<Sugar::Input::Vector<std::string>> names;
	configuration_item<int> age;
	configuration_item<double> height;
	component_with_arrays()
			:configurable_component_t("test", "This is a test"),
			 names("name", "Names of users", std::nullopt, RequirementLevel::Required),
			 age("age", "Age of the users", std::nullopt, RequirementLevel::Required),
			 height("height", "Heights of users", std::nullopt, RequirementLevel::Required)
	{
		register_item(names);
		register_item(age);
		register_item(height);

	};
};