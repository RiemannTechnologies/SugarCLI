#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <internal/string_convertor.h>
#include "component.h"
#include "runner.h"
#include "configuration_item.h"
namespace Sugar::CLI {
#pragma region test_specific_structure
    struct argc_argv{
    private:
        std::vector<char*> cstrings;
    public:

        argc_argv(std::vector<std::string> strings)
        {
            if(strings.empty()) throw std::invalid_argument("empty array given to structure");
            cstrings.reserve(strings.size());
            for(size_t i = 0; i < strings.size(); ++i)
                cstrings.push_back(const_cast<char*>(strings[i].c_str()));
        }
        [[nodiscard]] char** to_char_string_array() noexcept{
            return &this->cstrings[0];
        }
        [[nodiscard]] std::size_t argc() const noexcept{
            return cstrings.size();
        }
    };

#pragma endregion

    TEST(component_runner, argv_gets_converted_properly)
    {
        string_convertor converter;
        argc_argv test_args({"./myApp","--name","John","--age","25","--height","1.80"});

        ASSERT_EQ(test_args.argc(),7);
        ASSERT_EQ(converter.to_string_array(test_args.argc(),test_args.to_char_string_array()),
                  std::vector<std::string>({"./myApp","--name","John","--age","25","--height","1.80"}));
    }

    struct test_component : public component
    {
        configuration_item<std::string> name = configuration_item<std::string>("name");
        configuration_item<int> age = configuration_item<int>("age");
        configuration_item<double> height = configuration_item<double>("height");

        int run() override {
            SUCCEED();
            return 0;
        }
        explicit test_component() : component(){
            register_item(&name);
            register_item(&age);
            register_item(&height);
        }
    };

    TEST(component_api_test, api_flow)
    {
        test_component component;
        string_convertor convertor;
        runner r(&component);

        argc_argv args({"./myApp","--name","John","--age","25","--height","1.80"});
        argv_t argv_strings = convertor.to_string_array(args.argc(),args.to_char_string_array());
        ASSERT_EQ(argv_strings,std::vector<std::string>({"./myApp","--name","John","--age","25","--height","1.80"}));
        r.parsing_phase(args.argc(),args.to_char_string_array());
        ASSERT_EQ(component.name.value, "John");
        ASSERT_EQ(component.age.value, 25);
        ASSERT_EQ(component.height.value, 1.80);
        r.run_phase();


    }
}
