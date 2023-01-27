#pragma once

#include <string>
#include <functional>
#include <typeindex>

namespace Sugar::CLI {
struct configuration_option : public item {
  std::function<void(const ArgumentDatabase& context)> callback;

  explicit configuration_option(std::string name, std::string description,
		  std::function<void(const ArgumentDatabase& context)> callback,
		  std::type_index type)
		  :item(name, description),
		   callback(std::move(callback))
  {
  };

  void handle_opt(const ArgumentDatabase& args) override
  {
	  if (!(args.named_arguments.contains(long_name) || args.named_arguments.contains(short_name))) {
		  return;
	  }
	  if (!(args.named_arguments.at(long_name).empty() && args.named_arguments.at(short_name).empty())) {
		  throw std::runtime_error("Configuration options do NOT accept parameters "+long_name);
	  }
	  callback(args);
  }

  [[nodiscard]] std::string as_string() const override
  {
	  return "Configuration option";
  }
};
}