#include <iostream>
#include "parser_impl.h"

#define CONTAINER_CHECK_AND_APPLY(T) if(item.isContainer)\
od.add_options() \
        (item.name.c_str(),item.description.c_str(),cxxopts::value<std::vector<T>>()); \
else \
od.add_options() \
(item.name.c_str(),item.description.c_str(),cxxopts::value<T>());

#define CONTAINER_CHECK_AND_SETVAL(T)                            if (stub.isContainer) {\
component->set_value_for_item(name,vm[name].as<std::vector<T>>());\
} else {\
component->set_value_for_item(name, vm[name].as<T>());\
}
namespace Sugar::CLI {

/**
 * Initiate a parse of the argv
 * @param argc
 * @param argv
 */
void parser_impl::start_parse(int _argc, const char** _argv)
{

	pname = _argv[0];
	for (int i = 1; i<_argc; i++) {
		raw_arguments.emplace_back(_argv[i]);
	}

    if(_argc == 1)
        return;//TODO: show help
	std::string current_arg;
	for (auto i = 0; i<raw_arguments.size(); i++) {
		const auto& argument = raw_arguments[i];
		if (argument.starts_with("-")) {
			database.named_arguments.try_emplace(argument /* emplacing a default constructed object */);
			current_arg = argument;
		}
		else if (!current_arg.empty()) {
			database.named_arguments[current_arg].emplace_back(argument);
			current_arg = "";
		}
		else {
			database.positional_arguments.emplace_back(argument);
		}
	}

	obtain_argument_data_recursive(main);
}

void parser_impl::obtain_argument_data_recursive(configurable_component_t* component)
{

	for (const auto& kItem : component->items) {

		kItem.second->handle_opt(database);
	}
	if (component->children.empty() && component->child_component_switch != nullptr && !component->children.empty() &&
        component->child_component_switch == nullptr)

        throw std::runtime_error("Component {} has children but no child component switch"+component->id);
	if (component->children.empty())
		return;

	const auto switch_value = component->child_component_switch->as_string();
	obtain_argument_data_recursive(component->children[switch_value].get());
}
} // riemann