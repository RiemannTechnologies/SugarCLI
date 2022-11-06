#include "classes/complex_nested_component.h"


TEST(complex_nested_comp_test, FirstBranchBasicParse) {
    nested_component component;


    auto first_comp = std::static_pointer_cast<complex_child_component1>(component.children["first"]);
    auto second_comp = std::static_pointer_cast<complex_child_component2>(component.children["second"]);
    first_comp->is_called = false;


    const char *argv[] = {"./my_horn_is_very_orb", "--thing1", "first", "--height", "1.72", "--is_married", "true"};
    //, "--height", "1.72", "--is_married", "true"}:
    riemann::parser_impl parser(&component);
    int argc = sizeof(argv) / sizeof(const char *);

    parser.start_parse(argc, argv);

    ASSERT_EQ(first_comp->is_called, true);
    ASSERT_EQ(second_comp->is_called, false);
};
TEST(complex_nested_comp_test, SecondBranchBasicParse) {
    nested_component component;

    auto first_comp = std::static_pointer_cast<complex_child_component1>(component.children["first"]);
    auto second_comp = std::static_pointer_cast<complex_child_component2>(component.children["second"]);

    const char *argv[] = {"./my_horn_is_very_orb", "--thing2", "second", "--name", "ThonkDifferent", "--age", "16"};
    riemann::parser_impl parser(&component);
    int argc = sizeof(argv) / sizeof(const char *);

    parser.start_parse(argc, argv);

    ASSERT_EQ(first_comp->is_called, false);
    ASSERT_EQ(second_comp->is_called, true);
};