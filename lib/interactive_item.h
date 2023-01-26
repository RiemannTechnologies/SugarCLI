#pragma once

#include <iostream>
#include "configuration_item.h"
#include <sstream>
#include <functional>
#include <utility>
#include <IOStreamReader.h>
#include <IOException.h>

namespace Sugar::CLI {


    template<typename T>
    struct interactive_item : public item {
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
                : item(_name, _description,
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

        void set_value(CLI::Option *opt) override {
            this->value = opt->as<T>();
        }

        virtual T get_value() const {
            return value;
        }

        ~interactive_item() override = default;
      void set_option(std::string_view opt) override {
          opt->add_option(this->name, this->value, this->description);
      }


        void new_set_value_from_stream(std::istream &input, std::ostream &output) override{
          if (pre_stream_read_hook != nullptr)
            pre_stream_read_hook();

          if constexpr (is_container<T>::value && !std::is_same<std::string, T>::value) {
            bool OK = true;
            do {
              try {
                std::string s;
                std::getline(input, s, '\n');
                std::istringstream iss(s);
                sugar::m_IOStreamReader reader(input);
                std::remove_cvref_t<T> tmp;
                while (!iss.eof()) {
                  auto x = reader.m_TryRead(tmp);
                  if (x) {
                    reader.discard_line();
                    throw sugar::IOException(x);
                  }
                  this->value.emplace_back(tmp);
                }
              }
              catch (std::exception &e) {
                std::cout << "Invalid data\n";
                OK = false;
              }
            } while (!OK);
          } else {
            bool OK = true;
            do {
              try {
                sugar::m_IOStreamReader reader(input);
                auto x = reader.m_TryRead(this->value);
                if (x) {
                  reader.discard_line();
                  throw sugar::IOException(x);
                }
              }
              catch (std::exception &e) {
                std::cout << "Invalid data\n";
                OK = false;
              }
            }
            while (!OK);
          }
          if (post_stream_read_hook != nullptr)
            post_stream_read_hook();
        }


    };

};
