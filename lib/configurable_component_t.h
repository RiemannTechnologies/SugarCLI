#pragma once

#include <string>
#include <any>
#include <optional>
#include <map>
#include <typeinfo>
#include <stdexcept>
#include <utility>
#include <unordered_map>
#include "configuration_item.h"
#include "item.h"

namespace Sugar::CLI {

struct configurable_component_t {

  std::unordered_map<std::string, std::shared_ptr<configurable_component_t>> children;

  std::string id;//the string it should activate to when using the parser
  std::string help_text;//what should appear for the user in the help section

  std::vector<std::string> order;
  std::unordered_map<std::string, item*> items;
  item* child_component_switch = nullptr;//what should determine which component is called
  void register_item(item& _item);

  explicit configurable_component_t(std::string _id, std::string _help_text = "")
		  :id(std::move(_id)), help_text(std::move(_help_text))
  {
  };

  void register_child_component(std::shared_ptr<configurable_component_t> configurableComponent);

  virtual void run();

};

}
