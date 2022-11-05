#pragma once

#include <string>
#include <typeinfo>
#include <typeindex>
#include <any>

struct item {

    explicit item(std::string name, std::string description, std::type_index _id)
            : name(std::move(name)),
              description(std::move(description)),
              id(std::move(_id)) {
    }

    std::string name;
    std::string description;
    std::type_index id;


};

