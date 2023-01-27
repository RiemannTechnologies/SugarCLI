#include "classes/complex_component.h"

class complex_component_test : public testing::Test {
public:
	complex_component component;

};

TEST_F(complex_component_test, BasicCmdParse)
{
	component.is_called = false;
	const char* argv[] = {"./my_horn_is_very_orb", "--help"};
	riemann::parser_impl parser(&component);
	int argc = sizeof(argv)/sizeof(const char*);

	parser.start_parse(argc, argv);
	ASSERT_EQ(component.is_called, true);
};

TEST_F(complex_component_test, TestForErrorOverrideWhenOptionIsSpecified)
{
	component.is_called = false;
	const char* argv[] = {"./my_horn_is_very_orb", "--height", "1.72", "--age", "16", "--help"};
	riemann::parser_impl parser(&component);
	int argc = sizeof(argv)/sizeof(const char*);

	parser.start_parse(argc, argv);
	ASSERT_EQ(component.is_called, true);
}

TEST_F(complex_component_test, TestForOverrideWhenAllRequiredOptionsAreSpecified)
{
	component.is_called = false;
	const char* argv[] = {"./my_horn_is_very_orb", "--name", "ThonkDifferent", "--height", "1.72", "--age", "16",
						  "--is_married", "true", "--help"};
	riemann::parser_impl parser(&component);
	int argc = sizeof(argv)/sizeof(const char*);

	parser.start_parse(argc, argv);
	ASSERT_EQ(component.is_called, true);
}

//TODO: Better user-facing error messages
/*TEST_F(component_api_test, aeudfh) {
    const char *argv[] = {"./my_horn_is_very_orb", "sakjdajhf", "--name", "ThonkDifferent", "--height", "1.72", "--age",
                          "16",
                          "--favourite_letter", "chasd"};
    riemann::parser_impl parser(std::make_shared<configurable_component_t>(component));
    int argc = sizeof(argv) / sizeof(const char *);
    parser.start_parse(argc, argv);
    //ASSERT_ANY_THROW();

};*/