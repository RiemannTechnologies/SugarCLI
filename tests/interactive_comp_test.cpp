#include "classes/interactive_component.h"


class interactive_component_test : public testing::Test {
public:
    interactive_component component;

};

TEST_F(interactive_component_test, BasicCmdParse) {
    const char *argv[] = {"./my_horn_is_very_orb", "--name", "ThonkDifferent", "--height", "1.72", "--age", "16"};
    riemann::parser_impl parser(&component);
    int argc = sizeof(argv) / sizeof(const char *);

    parser.start_parse(argc, argv);
    ASSERT_EQ(component.name.get_value(), "ThonkDifferent");
    ASSERT_EQ(component.height.get_value(), 1.72);
    ASSERT_EQ(component.age.get_value(), 16);

}

TEST_F(interactive_component_test, CliInputTest) {
    const char *argv[] = {"./my_horn_is_very_orb"};
    riemann::parser_impl parser(&component);
    int argc = sizeof(argv) / sizeof(const char *);
    std::string input = "ThonkDifferent \n 17 \n 1.72 \n";
    std::istringstream in(input);
    std::ostringstream out;

    parser.m_input = &in;
    parser.m_output = &out;

    parser.start_parse(argc, argv);
    ASSERT_EQ(out.str(),
              component.name.asking_text + ": " + component.age.asking_text + ": " + component.height.asking_text +
              ": ");
}

TEST_F(interactive_component_test, CliInputErrorHandle) {
    const char *argv[] = {"./my_horn_is_very_orb"};
    riemann::parser_impl parser(&component);
    int argc = sizeof(argv) / sizeof(const char *);
    std::string input = place_on_new_lines("ThonkDifferent Amogus 17 1.73");
    spdlog::info("Got: "+ input);
    std::istringstream in(input);
    std::ostringstream out;

    parser.m_input = &in;
    parser.m_output = &out;

    parser.start_parse(argc, argv);
    spdlog::info("Process returned: " + out.str());
    ASSERT_EQ(out.str(),
              "Please input your name: Please input your age: \n"
              "Invalid data\n"
              "Please input your age: Please input your height: ");
}
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