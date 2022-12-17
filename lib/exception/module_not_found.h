#pragma once

#include <sstream>
#include "user_exception.hpp"

namespace riemann {
    class module_not_found_exception : public user_exception {
        std::string msg;
    public:
        explicit module_not_found_exception(const std::string &module, const cxxopts::Options &opt) {
            msg = module + "is not a valid option. Please consult the options below\n";
            msg += opt.help();
        };

        const char *what() const throw() {
            return msg.c_str();
        }
    };
}