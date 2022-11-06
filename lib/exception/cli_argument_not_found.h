#pragma once

#include <sstream>
#include "user_exception.hpp"

namespace riemann {
    class cli_argument_not_found_exception : public user_exception {
        std::string msg;
    public:
        explicit cli_argument_not_found_exception(const std::vector<std::string> &keys,
                                                  const po::options_description &opt) {
            std::stringstream stringstream;
            opt.print(stringstream);
            for (auto &entry: keys) {
                msg += "--" + entry + " could not be found and is required.\n";
            }
            msg += stringstream.str();
        };

        const char *what() const throw() {
            return msg.c_str();
        }
    };
}