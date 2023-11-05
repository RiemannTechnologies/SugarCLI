#include "item_api_mocks.h"
using ::testing::Return;
namespace Sugar::CLI {

    TEST(item_api_test, call_parse_method)
    {
        using T = std::string;
        item<T> testItem("testArg");
        mock_error_handling_strategy<T> testHandler;
        mock_parsing_strategy<T> testStrategy;
        testItem.errorHandler = &testHandler;
        testItem.parsingStrategy = &testStrategy;

        vmap testMap;
        testMap[testItem.arg_name] = {"John"};

        std::optional<T> result = "John";
        EXPECT_CALL(testStrategy,parse(testItem.arg_name,testMap))
                .Times(1)
                .WillOnce(Return(result));
        EXPECT_CALL(testHandler,error()).Times(0);

        testItem.parse(testMap);

        ASSERT_EQ(testItem.value,"John");
    }
    TEST(item_api_test, call_error_method)
    {
        using T = int;
        item<T> testItem("testArg");
        mock_error_handling_strategy<T> testHandler;
        mock_parsing_strategy<T> testStrategy;
        testItem.errorHandler = &testHandler;
        testItem.parsingStrategy = &testStrategy;

        vmap testMap;
        testMap[testItem.arg_name] = {"John"};

        std::optional<T> result = std::nullopt;
        EXPECT_CALL(testStrategy,parse(testItem.arg_name,testMap))
                .Times(1)
                .WillOnce(Return(result));

        error_handler_result<T> eResult = {42,false};
        EXPECT_CALL(testHandler,error())
                .Times(1)
                .WillOnce(Return(eResult));
        testItem.parse(testMap);

        ASSERT_EQ(testItem.value,42);
    }
    TEST(item_api_test, repeated_failiure_callbacks)
    {
        using T = int;
        item<T> testItem("testArg");
        mock_error_handling_strategy<T> testHandler;
        mock_parsing_strategy<T> testStrategy;
        testItem.errorHandler = &testHandler;
        testItem.parsingStrategy = &testStrategy;

        vmap testMap;
        testMap[testItem.arg_name] = {"John"};

        std::optional<T> result = std::nullopt;
        EXPECT_CALL(testStrategy,parse(testItem.arg_name,testMap))
                    .Times(1)
                    .WillOnce(Return(result));

        error_handler_result<T> eResult = {std::nullopt,true};
        error_handler_result<T> eResult2 = {42,false};
        EXPECT_CALL(testHandler,error())
                    .Times(2)
                    .WillOnce(Return(eResult))
                    .WillOnce(Return(eResult2));
        testItem.parse(testMap);

        ASSERT_EQ(testItem.value,42);
    }

}
