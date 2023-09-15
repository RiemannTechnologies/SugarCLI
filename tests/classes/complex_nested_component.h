#include <configuration_item.h>
#include <configurable_component_t.h>
#include <configuration_option.h>
#include <impl/parser_impl.h>
#include <gtest/gtest.h>
#include <memory>

using namespace Sugar::CLI;
class complex_child_component1 : public configurable_component_t {
public:
	configuration_item<double> height;
	configuration_item<bool> is_married;
	configuration_option thing1;

	bool is_called = false;

	complex_child_component1()
			:configurable_component_t("first", "This is the first component"),
			 height("height", RequirementLevel::Required, "Height of the user"),
			 is_married("is_married", RequirementLevel::Optional, "Is the user married", std::nullopt,false),
			 thing1("thing1", "a description", [this]([[
			 maybe_unused]] auto context) {
			   this->is_called = true;
			 })
	{
		register_item(height);
		register_item(is_married);
		register_item(thing1);
	}
};

class complex_child_component2 : public configurable_component_t {
public:
	configuration_item<std::string> name;
	configuration_item<int> age;
	configuration_option thing2;

	bool is_called = false;

	complex_child_component2()
			:configurable_component_t("second", "This is the second component"),
			 name("name", RequirementLevel::Required, "Name of the user"),
			 age("age", RequirementLevel::Required, "Age of the user"),
			 thing2("thing2", "a description", [this]([[
			 maybe_unused]] auto context) {
			   this->is_called = true;
			 })
	{
		register_item(name);
		register_item(age);
		register_item(thing2);
	};
};

class nested_component : public configurable_component_t {
public:

	configuration_item<std::string> action;//idfk
	nested_component()
			:configurable_component_t("test", "This is a test"),
			 action("action", RequirementLevel::Required, "Action to perform", 1)
	{
		register_item(action);
		child_component_switch = &action;
		register_child_component(std::make_shared<complex_child_component1>());
		register_child_component(std::make_shared<complex_child_component2>());
	};
};
