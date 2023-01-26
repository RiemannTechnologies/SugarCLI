#pragma once

#include <string>
#include <functional>
#include <typeindex>

namespace Sugar::CLI{

  namespace cli{
    struct configuration_option : public item {
      std::function<void(const std::size_t context)> callback;

      configuration_option(std::string name, std::string description,
                           std::function<void(const std::size_t context)> callback)
          : item(std::move(name), std::move(description), std::type_index(typeid(configuration_option))),
            callback(std::move(callback)) {
      };
      void set_option(std::string_view opt) override {
        opt->add_flag(this->name, this->description);
      }
    };
  }
}