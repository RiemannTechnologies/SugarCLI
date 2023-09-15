#pragma once

#include <iostream>

#include "configuration_item.h"
#include "util/strutil.hpp"
#include <SugarInput/lib/IOException.h>
#include <SugarInput/lib/Reader.h>
#include <SugarInput/lib/IOStreamable.h>
#include <SugarInput/lib/Parser.h>
namespace Sugar::CLI {



template<Input::IOStreamable T>
struct interactive_item : public configuration_item<T> {

public:
    bool has_optional_value = false;
    std::string user_message;
    std::istream* m_input = &std::cin;
    std::ostream* m_output = &std::cout;
	explicit interactive_item(std::string const& _name,
			std::string const& _user_message,
			RequirementLevel _level = RequirementLevel::Required,
			std::string const& _description = "",
			std::optional<int> _posArg = std::nullopt,
			std::optional<T> _default = std::nullopt)
			:configuration_item<T>(_name,
			_level,
			_description,
			_posArg,
			_default),
			 user_message(trim(_user_message))
	{
		if (_default!=std::nullopt) {
			has_optional_value = true;
		}
	}
	void handle_missing_argument([[maybe_unused]] ArgumentDatabase& args) override
	{
		bool ok = false;
		do {
			*m_output << user_message << ": ";

			try {
				Input::raw_input input;
				input = Input::Reader::Read(m_input);
				if (input.empty() && !this->has_optional_value) {
					*m_output << '\n';
					continue;
				}
				this->handle_sugar_input_parse(input);
				ok = true;
			}
			catch (std::invalid_argument&) {
				*m_output << "Invalid input, please try again" << std::endl;
			}
		}
		while (!ok);
	}

};
};
