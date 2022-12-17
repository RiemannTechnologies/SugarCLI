#pragma once

#include <sstream>
#include "user_exception.hpp"

namespace riemann {
    class cli_argument_not_found_exception : public user_exception {
        std::string msg;
    public:
        explicit cli_argument_not_found_exception(const std::vector<std::string> &keys,
                                                  const cxxopts::Options &opt) {
            for (auto &entry: keys) {
                msg += "--" + entry + " could not be found and is required.\n";
            }
            msg += opt.help();
        };

        [[nodiscard]] const char *what() const noexcept override {
            return msg.c_str();
        }
    };
}