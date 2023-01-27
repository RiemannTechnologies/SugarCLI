#include "configurable_component_t.h"

namespace Sugar::CLI {

void configurable_component_t::register_item(item& _item)
{
	this->order.push_back(_item.name);
	this->items.try_emplace(_item.name, &_item);
}

void configurable_component_t::register_child_component(
		std::shared_ptr<configurable_component_t> configurableComponent)
{
	children.try_emplace(configurableComponent->id, configurableComponent);
}

void configurable_component_t::run()
{
	const auto switch_value = child_component_switch->as_string();
	if (!switch_value.empty()) {
		children[switch_value]->run();
	}
	else
		throw std::runtime_error("The run function of "+id+" is not implemented."+"Did you forget to do so?");
}

}
