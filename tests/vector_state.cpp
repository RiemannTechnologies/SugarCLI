#include <gtest/gtest.h>
#include <internal/internal_vector_iterator.h>
namespace Sugar::CLI{

    TEST(vector_state, starting_index_should_be_0)
    {
        std::vector<std::string> example_vector = {"John", "Abe", "Logan", "Ian"};
        internal_vector_iterator iterator(example_vector);

        ASSERT_EQ(iterator.index, 0);
    }
    TEST(vector_state, advance_one_position)
    {

        std::vector<std::string> example_vector = {"John", "Abe", "Logan", "Ian"};
        internal_vector_iterator iterator(example_vector);
        ASSERT_EQ(iterator.array,example_vector);
        auto new_position = iterator.next();

        ASSERT_EQ(new_position.index, 1);
    }
    TEST(vector_state, at_the_end_of_the_vector_can_continue_return_false)
    {
        std::vector<std::string> example_vector = {"John", "Abe", "Logan", "Ian"};
        internal_vector_iterator iterator(example_vector);

        auto new_position = iterator.next().next().next();

        ASSERT_EQ(new_position.index, 3);
        ASSERT_FALSE(new_position.can_continue());
    }
    TEST(vector_state, when_at_end_do_not_continue_instead_keep_current_state)
    {
        std::vector<std::string> example_vector = {"John", "Abe", "Logan", "Ian"};
        internal_vector_iterator iterator(example_vector);

        auto new_position = iterator.next().next().next()
                .next();

        ASSERT_EQ(new_position.index, 3);
        ASSERT_FALSE(new_position.can_continue());
    }
    TEST(vector_state, can_continue_is_calculated_correctly)
    {
        std::vector<std::string> example_vector = {"John", "Abe", "Logan", "Ian"};
        internal_vector_iterator iterator(example_vector);

        ASSERT_TRUE(iterator.can_continue());
    }
    TEST(vector_state, get_current_value_test)
    {
        std::vector<std::string> example_vector = {"John", "Abe", "Logan", "Ian"};
        internal_vector_iterator iterator(example_vector);

        ASSERT_EQ(iterator.value(), "John");
    }
}