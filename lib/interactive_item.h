#pragma once

#include <iostream>
#include "configuration_item.h"
#include <sstream>
#include <functional>
#include <utility>


namespace riemann {

    struct interactive_item_stub : configuration_item_stub {
        std::string asking_text;

        explicit interactive_item_stub(const std::string &_name, const std::string &_description, RequirementLevel _lvl,
                                       std::optional<int> _pa, std::string _asking_text) :
                configuration_item_stub(_name, _description, _lvl, _pa),
                asking_text(std::move(_asking_text)) {
        }

        virtual void set_value_from_stream(std::istream &input, std::ostream &output) = 0;
        virtual ~interactive_item_stub() = default;
    };

    template<typename T>
    struct interactive_item : public interactive_item_stub {
    protected:
        T value;
        std::function<void()> pre_stream_read_hook;
        std::function<void()> post_stream_read_hook;
    public:
        /**
         * Create a new interactive item
         * @param _name Name of the item (ex. "help" will respond to --help)
         * @param _posArg Should it respond when there is no --option specified? And how many fields does can it respond to? (use -1 for all)
         * @param _default Default value if any
         */
        explicit interactive_item(const std::string &_name, const std::string &_description,
                                  const std::string &_asking_text, std::optional<int> _posArg = std::nullopt,
                                  std::optional<T> _default = std::nullopt)
                : interactive_item_stub(_name, _description,
                                        RequirementLevel::Required, _posArg, _asking_text) {
            if constexpr(is_container<T>::value && !std::is_same<std::string, T>::value) {
                tInfo = mapping[std::type_index(typeid(typename T::value_type))];
                isContainer = true;
            } else
                tInfo = mapping[std::type_index(typeid(T))];

            if (_default != std::nullopt)
                value = _default.value();

            this->id = std::type_index(typeid(interactive_item_stub));
        };

        void set_value(std::any val) override {
            this->value = std::any_cast<T>(val);
        }

        virtual T get_value() const {
            return value;
        }

        ~interactive_item() override = default;


        std::string int_to_str(int x)
        {
            std::string out;
            char tmpstr[1];
            switch(x)
            {
                case '\n':
                    out = "\n";
                    break;
                case ' ':
                    out = "<space>";
                    break;
                case EOF:
                    out = "EOF";
                    break;
                case 0:
                    out = "NULL";
                    break;
                default:
                    tmpstr[0] = (char)x;
                    out = tmpstr;
            }
            return out;

        }
        void handle_error_and_reset_istream(std::istream& input, std::ostream& output)
        {
            output << "\n";
            output << "Invalid data\n" << this->asking_text << ": ";
            std::string bad = input.fail() ? "true" : "false";
            spdlog::info("Bad() flag is: " + bad);
            input.clear();
            bad = input.fail() ? "true" : "false";
            spdlog::info("Bad() flag is: " + bad);

            spdlog::info("Skipping " + std::to_string(std::numeric_limits<std::streamsize>::max()) + " positions");
            input.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            spdlog::info("Current IOStream character: " + int_to_str(input.peek()));
        }

        void set_value_from_stream(std::istream &input, std::ostream &output) final override {
            if(pre_stream_read_hook != nullptr)
            {
                pre_stream_read_hook();
            }
            spdlog::info("Reading " + name);
            output << this->asking_text << ": ";

            if constexpr(is_container<T>::value && !std::is_same<std::string, T>::value) {
                //read each line and split it into tokens, then test each one for errors and add them to the value array
                std::istringstream line;
                std::string line_str;
                std::getline(input, line_str);
                line.str(line_str);
                //detect "" if it's a string
                if constexpr(std::is_same<typename T::value_type, std::string>::value) {

                    std::string token;

                    while (!line.eof()) {
                        while (!(line >> token)) {

                            handle_error_and_reset_istream(line, output);
                            std::getline(input,line_str);
                            line.str(line_str);
                        }
                        spdlog::info("Parsed " + token);
                        //all good, push back
                        value.push_back(token);
                    }
                } else {
                    typename T::value_type token; //create a possible entry of the type of the container objects
                    while (!line.eof()) {
                        while (!(line >> token)) {

                            handle_error_and_reset_istream(line, output);
                            std::getline(input,line_str);
                            line.str(line_str);
                        }
                        spdlog::info("Parsed " + token);
                        //all good, push back
                        value.push_back(token);
                    }
                }

            }
            else {
                if constexpr(std::is_same<std::string, T>::value) {
                    while (!(input >> value)) {

                        handle_error_and_reset_istream(input, output);
                    }
                    spdlog::info("Parsed " + value);
                } else {

                    while (!(input >> value)) {

                        handle_error_and_reset_istream(input, output);
                    }
                    spdlog::info("Parsed " + std::to_string(value));
                }
            }
            if(post_stream_read_hook != nullptr)
            {
                post_stream_read_hook();
            }
        };


    };

}