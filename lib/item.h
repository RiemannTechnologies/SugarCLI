#pragma once

#include <string>
#include <typeinfo>
#include <typeindex>
#include <any>
#include "typedefs.h"

namespace Sugar::CLI {
  struct item {
    std::string name;
    std::string description;
    std::string short_name;
    std::string long_name;
    /**
     * Initialize a new item
     *
     * if name has a "--" prefix, it will be removed
     * if name has a "-" prefix, it will be removed
     */
    explicit item(std::string _name, std::string description)
        : name(std::move(_name)),
          description(std::move(description))
    {
      int i = 0;
      while (name[i] == '-' && i < name.size()) { //skip all the dashes
        i++;
      }
      short_name = "-" + name.substr(i, 1);
      long_name = "--" + name.substr(i);
    }

    virtual void handle_opt(const ArgumentDatabase &args) = 0;
    virtual std::string as_string() const = 0;
   // virtual std::string generate_help() const = 0; TODO: implement this
  };
}