#include "classes/simple_nested_component.h"

TEST(nested_comp_test, FirstBranchBasicParse)
{
	nested_component component;
	const char* argv[] = {"./my_horn_is_very_orb", "first", "--height", "1.72", "--is_married", "true"};
	//, "--height", "1.72", "--is_married", "true"}:
	riemann::parser_impl parser(&component);
	int argc = sizeof(argv)/sizeof(const char*);

	parser.start_parse(argc, argv);

	auto height = static_cast<configuration_item<double>*>(component.children["first"]->items["height"]);
	auto is_married = static_cast<configuration_item<bool>*>(component.children["first"]->items["is_married"]);
	ASSERT_EQ(height->get_value(), 1.72);
	ASSERT_EQ(is_married->get_value(), true);
};
TEST(nested_comp_test, SecondBranchBasicParse)
{
	nested_component component;
	const char* argv[] = {"./my_horn_is_very_orb", "second", "--name", "ThonkDifferent", "--age", "16"};
	riemann::parser_impl parser(&component);
	int argc = sizeof(argv)/sizeof(const char*);

	parser.start_parse(argc, argv);

	auto name = static_cast<configuration_item<std::string>*>(component.children["second"]->items["name"]);
	auto age = static_cast<configuration_item<int>*>(component.children["second"]->items["age"]);
	ASSERT_EQ(name->get_value(), "ThonkDifferent");
	ASSERT_EQ(age->get_value(), 16);
};