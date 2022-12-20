#pragma once

#include <optional>
#include <typeindex>
#include <unordered_map>
#include "positional_argument_description.h"
#include "item.h"
#include "detect_container.h"
#include <any>
#include <spdlog/spdlog.h>
#include <IOStreamReader.h>
#include <CLI/CLI.hpp>

namespace riemann {
    enum class TypeInfo {
        String,
        Int,
        Bool,
        Char,
        Float,
        Double,
    };
    enum class RequirementLevel {
        Required,
        Optional,
        NotApplicable
    };

    static std::unordered_map<std::type_index, TypeInfo> mapping{
            {std::type_index(typeid(int)),         TypeInfo::Int},
            {std::type_index(typeid(std::string)), TypeInfo::String},
            {std::type_index(typeid(bool)),        TypeInfo::Bool},
            {std::type_index(typeid(char)),        TypeInfo::Char},
            {std::type_index(typeid(float)),       TypeInfo::Float},
            {std::type_index(typeid(double)),      TypeInfo::Double}
    };

//here go all the stuff that do NOT require the knowlegde of the exact information
    struct configuration_item_stub : public item {
        positionalArgumentDescription posArg;
        TypeInfo tInfo;
        bool isContainer = false;
        RequirementLevel requirementLevel = RequirementLevel::NotApplicable;

        configuration_item_stub(const std::string &name, const std::string &description, RequirementLevel level,
                                const std::optional<int> &posArg
        ) : item(name, description, std::type_index(typeid(configuration_item_stub))), posArg(posArg),
            requirementLevel(level) {}

        virtual void set_value(CLI::Option *opt) = 0;

    };

    template<typename T>
    class configuration_item : public configuration_item_stub {
    protected:
        T value;
    public:
        /**
         * Create a new configuration item
         * @param _name Name of the option (ex. "help" will respond to --help)
         * @param _posArg Should it respond when there is no --option specified? And how many fields does can it respond to? (use -1 for all)
         * @param _default Default value if any
         */
        explicit configuration_item(std::string _name, std::string _description,
                                    std::optional<int> _posArg, RequirementLevel _level,
                                    std::optional<T> _default = std::nullopt)

                : configuration_item_stub(_name, _description, _level, _posArg) {
            if (_level == RequirementLevel::Optional &&
                _posArg.has_value()) // positional operators are ALWAYS required for po
                spdlog::warn(
                        name +
                        " was set as optional. RequirementLevel::Optional has NO effect on positional options\n" +
                        "This could have undefined behavior. If you are an user of RBS, please report this issue");
            if constexpr(is_container<T>::value && !std::is_same<std::string, T>::value) {
                tInfo = mapping[std::type_index(typeid(typename T::value_type))];
                isContainer = true;
            } else
                tInfo = mapping[std::type_index(typeid(T))];


            if (_default != std::nullopt)
                value = _default.value();
        };


        void set_value(CLI::Option *opt) override {
            this->value = opt->as<T>();
        }

        virtual T get_value() const {
            return value;
        }

        virtual ~configuration_item() = default;
    };
}