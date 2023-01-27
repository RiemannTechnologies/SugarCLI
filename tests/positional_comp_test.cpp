#include "classes/simple_positional_component.h"

class positional_comp_test : public testing::Test {
public:
	positional_component component;

};

TEST_F(positional_comp_test, BasicCmdParse)
{
	const char* argv[] = {"./my_horn_is_very_orb", "ThonkDifferent", "16", "Thing1", "Thing2"};
	riemann::parser_impl parser(&component);
	int argc = sizeof(argv)/sizeof(const char*);

	parser.start_parse(argc, argv);
	ASSERT_EQ(component.name.get_value(), "ThonkDifferent");
	ASSERT_EQ(component.age.get_value(), 16);
	ASSERT_EQ(component.intrests.get_value().data, std::vector<std::string>({"Thing1", "Thing2"}));

};