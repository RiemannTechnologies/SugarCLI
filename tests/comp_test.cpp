#include "classes/simple_component.h"


class component_api_test : public testing::Test {
public:
    test_component component;

};

TEST_F(component_api_test, BasicCmdParse) {
    const char *argv[] = {"./my_horn_is_very_orb", "--name", "ThonkDifferent", "--height", "1.72", "--age", "16"};
    riemann::parser_impl parser(&component);
    int argc = sizeof(argv) / sizeof(const char *);

    parser.start_parse(argc, argv);
    ASSERT_EQ(component.name.get_value(), "ThonkDifferent");
    ASSERT_EQ(component.height.get_value(), 1.72);
    ASSERT_EQ(component.age.get_value(), 16);

};

/*TEST_F(component_api_test, TestForCmdParseErr) {//FIXME: This test is not working
    const char *argv[] = {"./my_horn_is_very_orb", "--height", "1.72", "--age", "16"};
    riemann::parser_impl parser(&component);
    int argc = sizeof(argv) / sizeof(const char *);

    EXPECT_THROW(parser.start_parse(argc, argv), riemann::user_exception);
}*/

TEST_F(component_api_test, TestOptionalHandling) {
    const char *argv[] = {"./my_horn_is_very_orb", "--name", "ThonkDifferent", "--height", "1.72", "--age", "16",
                          "--is_married", "true"};
    riemann::parser_impl parser(&component);
    int argc = sizeof(argv) / sizeof(const char *);

    parser.start_parse(argc, argv);
    ASSERT_EQ(component.is_married.get_value(), true);
}

TEST_F(component_api_test, TestAllVals) {
    const char *argv[] = {"./my_horn_is_very_orb", "--name", "ThonkDifferent", "--height", "1.72", "--age", "16",
                          "--is_married", "true", "--favourite_letter", "C"};

    riemann::parser_impl parser(&component);
    int argc = sizeof(argv) / sizeof(const char *);


    parser.start_parse(argc, argv);
    ASSERT_EQ(component.name.get_value(), "ThonkDifferent");
    ASSERT_EQ(component.height.get_value(), 1.72);
    ASSERT_EQ(component.age.get_value(), 16);
    ASSERT_EQ(component.is_married.get_value(), true);
    ASSERT_EQ(component.favourite_letter.get_value(), 'C');
};

TEST_F(component_api_test, TestCharParse) {
    const char *argv[] = {"./my_horn_is_very_orb", "--name", "ThonkDifferent", "--height", "1.72", "--age", "16",
                          "--favourite_letter", "chasd"};
    riemann::parser_impl parser(&component);
    int argc = sizeof(argv) / sizeof(const char *);

    ASSERT_ANY_THROW(parser.start_parse(argc, argv));

};
//TODO: Better user-facing error messages
/*TEST_F(component_api_test, aeudfh) {
    const char *argv[] = {"./my_horn_is_very_orb", "sakjdajhf", "--name", "ThonkDifferent", "--height", "1.72", "--age",
                          "16",
                          "--favourite_letter", "chasd"};
    riemann::parser_impl parser(std::make_shared<riemann::configurable_component_t>(component));
    int argc = sizeof(argv) / sizeof(const char *);
    parser.start_parse(argc, argv);
    //ASSERT_ANY_THROW();

};*/