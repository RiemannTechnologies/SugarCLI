//
// Created by thonk on 09.02.2022.
//

#pragma once

#include <exception>
#include <string>

namespace riemann {
    class user_exception : public std::exception {
    public:
        virtual const char *what() const throw() {
            return "";
        };
    };
}