#pragma once

#include <string>
#include <functional>
#include <typeindex>

namespace Sugar::CLI {
struct configuration_option : public item {
private:
    bool isNotEmpty(const ArgumentDatabase& db, std::string toLookup)
    {
        if(db.named_arguments.contains(toLookup))
        {
            if(db.named_arguments.at(toLookup).empty())
                return false;
            return true;
        }
        return false;
    }
public:
  std::function<void(const ArgumentDatabase& context)> callback;

  explicit configuration_option(std::string name, std::string description,
		  std::function<void(const ArgumentDatabase& context)> callback)
		  :item(name, description),
		   callback(std::move(callback))
  {
  };

  void handle_opt(ArgumentDatabase& args) override
  {
	  if (!(args.named_arguments.contains(long_name) || args.named_arguments.contains(short_name))) {
		  return;
	  }
	  if (isNotEmpty(args,long_name) && isNotEmpty(args,short_name)){
		  throw std::runtime_error("Configuration options do NOT accept parameters "+long_name);
	  }
      args.shouldStop = true;
      args.errors.clear();
	  callback(args);
  }

  [[nodiscard]] std::string as_string() const override
  {
	  return "Configuration option";
  }
};
}