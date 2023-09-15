#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>

namespace Sugar::CLI{
  enum class RequirementLevel {
    Required,
    Optional
  };
  enum class ErrorType{
      ArgumentNotFound,
      Unknown
  };
  typedef std::map<std::string,std::vector<std::string>> named_argument_database;

  struct ArgumentDatabase{
    std::vector<std::string> positional_arguments;
    named_argument_database named_arguments;
    std::size_t current_positional_position = 0;
    std::map<ErrorType,std::string> errors;
    bool shouldStop = false;
  };
}