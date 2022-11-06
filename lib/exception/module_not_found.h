#pragma once

#include <sstream>
#include "user_exception.hpp"
#include <boost/program_options.hpp>

namespace po = boost::program_options;
namespace riemann {
    class module_not_found_exception : public user_exception {
        std::string msg;
    public:
        explicit module_not_found_exception(const std::string &module, const po::options_description &opt) {
            msg = module + "is not a valid option. Please consult the options below\n";
            std::stringstream str;
            opt.print(str);
            msg += str.str();
        };

        const char *what() const throw() {
            return msg.c_str();
        }
    };
}