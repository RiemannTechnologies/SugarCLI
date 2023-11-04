#include <gtest/gtest.h>
#include "internal/type_definitions.h"
#include <sstream>

namespace Sugar::CLI {

    /*TEST(error_handler,handler_returns_new_value_and_the_repeat_flag_to_no)
    {
        interactive_handling_procedure<std::string> procedure;
        std::istringstream fake_input("John\n");
        std::ostringstream test_output;

        procedure.input_stream = fake_input;
        procedure.output_stream = test_output;

        error_handler_result<std::string> result;
        ASSERT_NO_THROW(result = procedure.error());
        ASSERT_FALSE(result.shouldTryAgain);
        ASSERT_NE(result.newValue, std::nullopt);
        ASSERT_EQ(result.newValue, "John");
    }
    TEST(error_handler,handler_returns_value_containing_spaces_and_sets_the_repeat_flag_to_no)
    {
        interactive_handling_procedure<std::string> procedure;
        std::istringstream fake_input("\"John Davis\"\n");
        std::ostringstream test_output;

        procedure.input_stream = fake_input;
        procedure.output_stream = test_output;

        error_handler_result<std::string> result;
        ASSERT_NO_THROW(result = procedure.error());
        ASSERT_FALSE(result.shouldTryAgain);
        ASSERT_NE(result.newValue, std::nullopt);
        ASSERT_EQ(result.newValue, "John Davis");
    }
    TEST(error_handler,handler_gracefully_handles_mallformed_input_and_sets_the_repeat_flag_to_yes)
    {
        interactive_handling_procedure<int> procedure;
        std::istringstream fake_input("\"John Davis\"\n");
        std::ostringstream test_output;

        procedure.input_stream = fake_input;
        procedure.output_stream = test_output;

        error_handler_result<int> result;
        ASSERT_NO_THROW(result = procedure.error());
        ASSERT_TRUE(result.shouldTryAgain);
        ASSERT_EQ(result.newValue, std::nullopt);
    }
    TEST(error_handler,handler_does_not_move_the_read_head_on_istream_too_far_on_failiure) //if this fails it will be a massive headache to fix
    {
        interactive_handling_procedure<int> procedure;
        std::istringstream fake_input("\"John Davis\"\nThis Should Not Be Read\n");
        std::ostringstream test_output;

        procedure.input_stream = fake_input;
        procedure.output_stream = test_output;

        error_handler_result<int> result;
        ASSERT_NO_THROW(result = procedure.error());
        ASSERT_TRUE(result.shouldTryAgain);
        ASSERT_EQ(result.newValue, std::nullopt);
        ASSERT_FALSE(fake_input.eof());
    }
    TEST(error_handler,handler_does_not_move_the_read_head_on_istream_too_far_on_success)
    {
        interactive_handling_procedure<std::string> procedure;
        std::istringstream fake_input("\"John Davis\"\nThis Should Not Be Read\n");
        std::ostringstream test_output;

        procedure.input_stream = fake_input;
        procedure.output_stream = test_output;

        error_handler_result<std::string> result;
        ASSERT_NO_THROW(result = procedure.error());
        ASSERT_FALSE(result.shouldTryAgain);
        ASSERT_NE(result.newValue, std::nullopt);
        ASSERT_EQ(result.newValue, "John Davis");
        ASSERT_FALSE(fake_input.eof());
    }*/
}
