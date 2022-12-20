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
namespace riemann {

    /**
     * Initiate a parse of the argv
     * @param argc
     * @param argv
     */
    void parser_impl::start_parse(int _argc, const char **_argv) {
        this->argc = _argc;
        this->argv = _argv;
        this->pname = argv[0];
        spdlog::info("Parse Started");
        new_build_po_recursive(main);
        spdlog::info("OD built");
        new_parse_component(main);
    }
/*
    void parser_impl::main_parse_recursive_loop(configurable_component_t *component) {
        spdlog::info("in main recurse loop");
        if (parse_component(component) == parse_result::CanContinue && !component->children.empty()) {
            if (component->child_component_switch.empty())
                throw std::runtime_error(
                        component->id + " has children, but no switch variable. Parsing can't continue");
            else {
                const auto switch_value = static_cast<configuration_item<std::string> *>(component->items[component->child_component_switch])->get_value();
                spdlog::info("continuing parse");
                if (!component->children.contains(switch_value)) {
                    throw riemann::module_not_found_exception(
                            switch_value, od);
                }
                main_parse_recursive_loop(
                        component->children[switch_value].get());
            }
        }
    }*/
    /**
     * Parse one component
     * @param component component to be parsed
     */

    void parser_impl::new_build_po_recursive(configurable_component_t *component)
    {
        for (auto &item : component->items) {
          const auto &_item = item.second;

          const auto &stub = (configuration_item_stub &) *_item;

          //tell CLI11 about the configuration option stuff
          if(_item->id == typeid(configuration_option))
          {
            const auto& option = (configuration_option&)*_item;
            component->app->add_flag(option.name,option.callback,option.description);
            continue;
          }
          bool isRequired = _item->id==(typeid(configuration_item_stub))          &&
                            stub.requirementLevel == RequirementLevel::Required;// only configuration items can have requirement levels
          CLI::Option* opt = nullptr;

          switch (stub.tInfo)
          {
            case TypeInfo::Bool:
              component->app->add_flag(item.first, item.second->description);
              continue;
              break;
            default:
              if(stub.isContainer)
              {
                opt = component->app->add_option(item.first, item.second->description)->required(isRequired)->expected(-1);
              }
              else
              {
                opt = component->app->add_option(item.first, item.second->description)->required(isRequired);
              }
              break;
          }
          if(stub.posArg.isSet())
          {
              opt->expected(stub.posArg);
          }
        }
        if(!component->children.empty())
        {
          for(auto& child : component->children)//string,unique_ptr<configurable_component_t>
          {
            new_build_po_recursive(child.second.get());
          }
        }
    }
    int parser_impl::new_parse_component(configurable_component_t *component){
        spdlog::info("parsing component {}", component->id);
        new_build_po_recursive(component);
        CLI11_PARSE(*component->app, argc, argv);
        for(auto& item : component->items) //string, unique_ptr<configuration_item_base>
        {
          auto& _item = item.second;
            auto& stub = (configuration_item_stub&)*_item;
        }
        return 0;
    }
/*
    parse_result parser_impl::parse_component(configurable_component_t *component) {


        //Now it's time to build od and pod.
        //We'll add each component's pod and od to the mix, until a _com_str that makes
        //sense is formed.
        build_od(component);
        spdlog::info("OD built");
        /* Apparently allow_unregistered() kind of breaks when it is used in conjunction with positional
         options. As such, we will create a dummy positional option to collect everything that isn't (yet) recognized*/
        /*cxxopts::Options _od = od;
        if (!component->children.empty()) {
            _od.add_options()
                    ("candice", "",cxxopts::value<std::vector<std::string>>());
            pod.emplace_back("candice");

        }

        //Now we'll parse the arguments with the positional arguments and options we've built
        _od.parse_positional(pod.begin(),pod.end());
        vm = _od.parse(argc, argv);

        std::vector<std::string> errors;//here we store all the missing options, so we can yell at our users
        std::vector<item *> error_items;
        for (auto const &in: component->order) {
            //keep insertion order
            auto &name = in;
            auto &it = component->items[name];
            spdlog::info("Processing OD for " + name);
            if (it->id == typeid(configuration_item_stub) ||
                it->id == typeid(interactive_item_stub)) //it's a config item, so let's put the values in
            {
                const auto &stub = (configuration_item_stub &) *it;
                if (vm.count(name)) {
                    switch (stub.tInfo) {

                        case TypeInfo::String:
                            CONTAINER_CHECK_AND_SETVAL(std::string)
                            break;
                        case TypeInfo::Int:
                            CONTAINER_CHECK_AND_SETVAL(int)
                            break;
                        case TypeInfo::Bool:
                            CONTAINER_CHECK_AND_SETVAL(bool)
                            break;
                        case TypeInfo::Char:
                            CONTAINER_CHECK_AND_SETVAL(char)
                            break;
                        case TypeInfo::Float:
                            CONTAINER_CHECK_AND_SETVAL(float)
                            break;
                        case TypeInfo::Double:
                            CONTAINER_CHECK_AND_SETVAL(double)
                            break;
                    }
                } else {
                    if (stub.requirementLevel == RequirementLevel::Required) {
                        //we save each option that was not found so that if we have a configuration **option**, the program shouldn't
                        //notify the user that an option is missing
                        error_items.push_back(it);
                    }
                }
            } else if (it->id == typeid(configuration_option)) {
                const auto &opt = (configuration_option &) *it;
                if (vm.count(name)) {
                    opt.callback(od);
                    return parse_result::MustBreak;
                }
            }
        }
        if (!error_items.empty()) {
            bool should_throw = false;
            for (auto x: error_items) {
                spdlog::info("Preparing to ask for " + x->name);
                if (x->id == typeid(interactive_item_stub)) {
                    auto &stub = (configuration_item_stub &) *x;
                    auto &istub = dynamic_cast<interactive_item_stub &> (stub);
                    spdlog::info("setting value from stream - " + x->name);
                    istub.set_value_from_stream(*m_input, *m_output);
                } else {
                    should_throw = true;
                    errors.push_back(x->name);
                }
            }
            if (should_throw)
                throw cli_argument_not_found_exception(errors, od);
        }

        return parse_result::CanContinue;
    }

    void parser_impl::build_od(configurable_component_t *component) {
        for (auto const &it: component->order) {
            //keep insertion order
            auto &name = it;
            auto &comp = component->items[name];

            spdlog::info("building OD");

            if (comp->id == typeid(configuration_item_stub) || comp->id == typeid(interactive_item_stub)) {
                const auto &item = (configuration_item_stub &) *comp;
                switch (item.tInfo) {
                    case TypeInfo::Int:
                        CONTAINER_CHECK_AND_APPLY(int)
                        break;
                    case TypeInfo::String:
                        CONTAINER_CHECK_AND_APPLY(std::string)
                        break;
                        //TODO: bool_switch for Boolean values
                    case TypeInfo::Bool:
                        CONTAINER_CHECK_AND_APPLY(bool)
                        break;
                    case TypeInfo::Char:
                        CONTAINER_CHECK_AND_APPLY(char)
                        break;
                    case TypeInfo::Float:
                        CONTAINER_CHECK_AND_APPLY(float)
                        break;
                    case TypeInfo::Double:
                        CONTAINER_CHECK_AND_APPLY(double)
                        break;
                }
                if (item.posArg.isSet()) {
                    pod.push_back(item.name);
                    for(int i = 2; i <= item.posArg; i++) //ensure that the program can respect the maximum admitted number of positional
                                                          //arguments that the option configured
                                                        //TODO: find a way to handle just 1 positional argument(although I am not sure if it's really needed
                        pod.push_back(item.name);
                }
            }
            if (comp->id == typeid(configuration_option)) {
                od.add_options()
                        (comp->name, comp->description);
            }
        }
    }*/
} // riemann