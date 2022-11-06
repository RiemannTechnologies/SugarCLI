#include "configurable_component_t.h"

namespace riemann {


    void configurable_component_t::register_item(item &_item) {
        this->order.push_back(_item.name);
        this->items.try_emplace(_item.name, &_item);
        spdlog::info("[COMPONENT API] " + _item.name + " was registered successfully");
    }

    void configurable_component_t::register_child_component(
            std::shared_ptr<configurable_component_t> configurableComponent) {
        children.try_emplace(configurableComponent->id,
                             configurableComponent);
        spdlog::info("[COMPONENT API] Component " + configurableComponent->id +
                     " was registered successfully as a child of " + id);
    }

    void configurable_component_t::set_value_for_item(const std::string &it, const std::any &value) {
        auto _itm = static_cast<configuration_item_stub *>(this->items[it]);
        _itm->set_value(value);
    }

    void configurable_component_t::run() {
        const auto switch_value = static_cast<configuration_item<std::string> *>(items[child_component_switch])->get_value();
        if (!switch_value.empty()) {
            children[switch_value]->run();
        } else
            throw std::runtime_error("The run function of " + id + " is not implemented." + "Did you forget to do so?");
    }

}
