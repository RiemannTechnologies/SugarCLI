#pragma once

#include <string>
#include "requirement.h"
#include "cli_envinronment.h"
namespace Sugar::CLI {
    template<typename T> requires Input::IOStreamable<T>
    struct item {
      T value;
      std::string name;
      std::string description;
      requirement_t requirement;
      virtual bool matcher (const cli_environment& env) = 0;
      virtual std::vector<std::string_view> match_id() const = 0;
      virtual void success () = 0;
      virtual void fail () = 0;
      virtual ~item() = default;

      explicit item(const std::string& _name,
                    const std::string& _description,
                    const requirement_val_t& _requirement) :
                    name(_name), description(_description), requirement(_requirement)
                    {};

  };
}