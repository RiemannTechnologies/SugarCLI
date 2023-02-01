#pragma once

#include <optional>
#include <typeindex>
#include <unordered_map>
#include "positional_argument_description.h"
#include "item.h"
#include <any>
#include <sstream>
#include <SugarInput/lib/Reader.h>
#include <SugarInput/lib/Parser.h>
#include <SugarInput/lib/Datatypes/Vector.h>
#include <SugarInput/lib/IOStreamable.h>

namespace Sugar::CLI {
template<typename T> requires Input::IOStreamable<T>
class configuration_item : public item {

protected:
	T value;
	positionalArgumentDescription pad;
	RequirementLevel level;
	bool is_set = false;

	void handle_sugar_input_parse(Input::raw_input& input)
	{
		if constexpr (!std::is_base_of_v<Input::UserIOStreamable, T>)//make this less sobful
		{
			Input::Parser::Parse(value, input[0]);
		}
		else {
			Input::Parser::Parse(value, input);
		}
	}
	void retrieve_positional_arguments(const ArgumentDatabase& args)
	{
		if (!pad.isSet()) return;
		Input::raw_input input;
		if (pad.value()==-1) {
			input.resize(args.positional_arguments.size()-args.current_positional_position);
			for (auto i = args.current_positional_position; i<args.positional_arguments.size(); ++i) {
				input.emplace_back(args.positional_arguments[i]);
				is_set = true;
			}
		}
		else {
			input.resize(pad.value());
			for (auto i = args.current_positional_position; i<args.positional_arguments.size() && i<i+pad.value();
				 ++i) {
				input.emplace_back(args.positional_arguments[i]);
				is_set = true;
			}
			input.shrink_to_fit();
		}
		handle_sugar_input_parse(input);
	}

	virtual void handle_missing_argument()
	{
		if (level==RequirementLevel::Optional) return;
		throw std::invalid_argument(name+" is required, but was not provided");
	}
public:
	/**
	 * Create a new configuration item
	 * @param _name Name of the option (ex. "help" will respond to --help)
	 * @param _posArg Should it respond when there is no --option specified? And how many fields does can it respond to? (use -1 for all)
	 * @param _default Default value if any
	 */
	explicit configuration_item(std::string _name,
			RequirementLevel _level = RequirementLevel::Optional,
			std::string _description = "",
			std::optional<int> _posArg = std::nullopt,
			std::optional<T> _default = std::nullopt)

			:item(_name, _description), level(_level), pad(_posArg)
	{
		if (_default!=std::nullopt) {
			value = _default.value();
		}
        if(_posArg==std::nullopt)
            return;
		if constexpr (std::is_base_of_v<Input::Containter, T>) {
			if (_posArg.value()==1)
				throw std::invalid_argument(name+" is a collection, but it only accepts 1 parameter");
		}
		else {
			if (_posArg.value()!=1)
				throw std::invalid_argument(
						name+" is not a collection, but it is configured to accept more than 1 parameter");
		}
	};

	void handle_opt(const ArgumentDatabase& args) override
	{
		if (pad.isSet()) {
			retrieve_positional_arguments(args);
			if (!is_set)
				handle_missing_argument();
			else
				return;
		}
		if (!args.named_arguments.contains(long_name) || !args.named_arguments.contains(short_name))
			handle_missing_argument();
		else
			return;
		Input::raw_input input = args.named_arguments.at(long_name);

		for (const auto& argValue : args.named_arguments.at(short_name))
			input.emplace_back(argValue);
		handle_sugar_input_parse(input);
	}
	[[nodiscard]] std::string as_string() const override
	{
		if constexpr (std::is_base_of_v<Input::Containter, T>) {
			std::stringstream ss;
			for (const auto& v : value.data) {
				ss << v << " ";
			}
			return ss.str();
		}
		else if constexpr (std::is_same_v<T, std::string>) {
			return value;
		}
		else
			return std::to_string(value);
	}
	virtual T get_value() const
	{
		return value;
	}

};
}