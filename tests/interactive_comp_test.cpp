#include "classes/interactive_component.h"


class interactive_component_test : public testing::Test {
public:
	interactive_component component;
};

TEST_F(interactive_component_test, BasicCmdParse)
{
	const char* argv[] = {"./my_horn_is_very_orb", "--name", "ThonkDifferent", "--height", "1.72", "--age", "16"};
	parser_impl parser(&component);
	int argc = sizeof(argv)/sizeof(const char*);

	parser.start_parse(argc, argv);
	ASSERT_EQ(component.name.get_value(), "ThonkDifferent");
	ASSERT_EQ(component.height.get_value(), 1.72);
	ASSERT_EQ(component.age.get_value(), 16);

}

TEST_F(interactive_component_test, CliInputTest)
{
	const char* argv[] = {"./my_horn_is_very_orb"};
	parser_impl parser(&component);
	int argc = sizeof(argv)/sizeof(const char*);
	std::string input = "ThonkDifferent \n 17 \n 1.72 \n";
	std::istringstream in(input);
	std::ostringstream out;

    component.set_io_for_components(&in,&out);

	parser.start_parse(argc, argv);
	ASSERT_EQ(out.str(),
			component.name.user_message+": "+component.age.user_message+": "+component.height.user_message+
					": ");
}

TEST_F(interactive_component_test, CliInputErrorHandle)
{
	const char* argv[] = {"./my_horn_is_very_orb"};

    interactive_component mock_component;
    parser_impl parser(&mock_component);
	int argc = sizeof(argv)/sizeof(const char*);
	std::string input = place_on_new_lines("ThonkDifferent Amogus 17 1.73");

	std::istringstream in(input);
	std::ostringstream out;

    mock_component.set_io_for_components(&in,&out);

	parser.start_parse(argc, argv);
    EXPECT_CALL(mock_component.age,handle_invalid_args())
                                    .Times(1);
}
//TODO: Better user-facing error messages
/*TEST_F(component_api_test, aeudfh) {
    const char *argv[] = {"./my_horn_is_very_orb", "sakjdajhf", "--name", "ThonkDifferent", "--height", "1.72", "--age",
                          "16",
                          "--favourite_letter", "chasd"};
    parser_impl parser(std::make_shared<configurable_component_t>(component));
    int argc = sizeof(argv) / sizeof(const char *);
    parser.start_parse(argc, argv);
    //ASSERT_ANY_THROW();

};*/