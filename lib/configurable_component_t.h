#pragma once

#include <string>
#include <boost/program_options.hpp>
#include <boost/preprocessor.hpp>
#include <any>
#include <optional>
#include <map>
#include <typeinfo>
#include <stdexcept>
#include <utility>
#include <unordered_map>
#include "configuration_item.h"
#include "spdlog/include/spdlog/spdlog.h"
#include "item.h"

namespace po = boost::program_options;
namespace riemann {

    struct configurable_component_t {

        std::unordered_map<std::string, std::shared_ptr<configurable_component_t>> children;

        std::string id;//the string it should activate to when using the parser
        std::string help_text;//what should appear for the user in the help section

        std::vector<std::string> order;
        std::unordered_map<std::string, item *> items;
        std::string child_component_switch;//what should determine which component is called

        void register_item(item &_item);

        /**
         * Initialize a component
         * @param _id the string it should activate to when using the parser
         * @param _help_text what should appear for the user in the help section
         */
        explicit configurable_component_t(std::string _id, std::string _help_text = "")
                : id(std::move(_id)), help_text(std::move(_help_text)) {

        };

        void set_value_for_item(const std::string &it, const std::any &value);

        void register_child_component(std::shared_ptr<configurable_component_t> configurableComponent);

        virtual void run();

    };



    //sometimes, you want to run an action when you see a parameter, but you do not want to store
    //its value because it does not have one. As such, you can initialize an "option" that contains
    //the same parameters as a normal config item, but now it has a function callback you can use
    //to run any code of your liking

    struct configuration_option : public item {
        std::function<void(const po::options_description &context)> callback;

        configuration_option(std::string name, std::string description,
                             std::function<void(const po::options_description &context)> callback)
                : item(std::move(name), std::move(description), std::type_index(typeid(configuration_option))),
                  callback(std::move(callback)) {
        };

    };


}
//