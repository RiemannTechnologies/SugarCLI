#pragma once

#include <configuration_item.h>
#include <configurable_component_t.h>
#include <impl/parser_impl.h>
#include <gtest/gtest.h>
#include <memory>

using namespace Sugar::CLI;
class positional_component : public configurable_component_t {
public:

	configuration_item<std::string> name;
	configuration_item<int> age;
	configuration_item<Sugar::Input::Vector<std::string>> intrests;

	positional_component()
			:configurable_component_t("test", "This is a test"),
			 name("name", RequirementLevel::Required, "Name of the user"),
			 age("age", RequirementLevel::Required, "Age of the user"),
			 intrests("things", RequirementLevel::Required, "Interests",-1)
	{
		register_item(name);
		register_item(age);
		register_item(intrests);

	};
};
