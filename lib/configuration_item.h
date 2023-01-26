#pragma once

#include <optional>
#include <typeindex>
#include <unordered_map>
#include "positional_argument_description.h"
#include "item.h"
#include "detect_container.h"
#include <any>
#include <spdlog/spdlog.h>
#include <IOStreamReader.h>
#include <CLI/CLI.hpp>

namespace Sugar::CLI {

    template<typename T>
    class configuration_item : public item {
    protected:
        T value;
        positionalArgumentDescription pad;
        RequirementLevel level;
    public:
        /**
         * Create a new configuration item
         * @param _name Name of the option (ex. "help" will respond to --help)
         * @param _posArg Should it respond when there is no --option specified? And how many fields does can it respond to? (use -1 for all)
         * @param _default Default value if any
         */
        explicit configuration_item(std::string _name, std::string _description,
                                    std::optional<int> _posArg, RequirementLevel _level = RequirementLevel::Optional,
                                    std::optional<T> _default = std::nullopt)

                : item(_name, _description), level(_level) {
            if (_level == RequirementLevel::Optional && _posArg.has_value()) // positional operators are ALWAYS required for po
                spdlog::warn(
                        _name +
                        " was set as optional. RequirementLevel::Optional has NO effect on positional options\n" +
                        "This could have undefined behavior.");
            if (_default != std::nullopt)
            {
              value = _default.value();
            }
          if constexpr (is_container<T>::value && !std::is_same<std::string, T>::value)
          {
            if(_posArg.value() == 1)
              throw std::runtime_error(name + " is a collection, but it only accepts 1 parameter");
          }
          else
          {
            if(_posArg.value() != -1)
              throw std::runtime_error(name + " is not a collection, but it is configured to accept more than 1 parameter");
          }
        };

      void handle_opt(const ArgumentDatabase &args) override {
        if(pad.isSet())
        {
          bool got_input = false;
          if(pad.value() == -1) {
            for (auto i = args.current_positional_position; i < args.positional_arguments.size(); ++i) {
              got_input = true;
              value.emplace_back(args.positional_arguments[i]);
            }
          }
          else {
            for (auto i = args.current_positional_position; i < args.positional_arguments.size() && i < i + pad.value();
                 ++i) {
              got_input = true;
              if constexpr (is_container<T>::value && !std::is_same<std::string, T>::value) {
                value.emplace_back(args.positional_arguments[i]);
              } else {
                value = args.positional_arguments[i];
              }
            }
          }
          if(!got_input && level == RequirementLevel::Required)
            throw std::runtime_error(name + " is required but was not set"); //TODO: Make this print help messages

          return;
        }

        if constexpr (is_container<T>::value && !std::is_same<std::string, T>::value)
        {
          value
        }

      }
      [[nodiscard]] std::string as_string() const override {
        if constexpr (is_container<T>::value && !std::is_same<std::string, T>::value) {
          std::stringstream ss;
          for (const auto &v : value) {
            ss << v << " ";
          }
          return ss.str();
        } else {
          return std::to_string(value);
        }
      }
      virtual T get_value() const {
            return value;
        }

        virtual ~configuration_item() = default;
    };
}