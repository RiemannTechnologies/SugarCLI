#pragma once

#include <climits>
#include <stdexcept>
#include <optional>

class positionalArgumentDescription {
    int pargs = INT_MIN;
public:
    void testVal(int _nrargs) {
        if (_nrargs < -1)
            throw std::invalid_argument("Invalid positional argument number");
        pargs = _nrargs;
    }

    explicit positionalArgumentDescription(std::optional<int> _nrargs) {
        if (_nrargs != std::nullopt)
            testVal(_nrargs.value());
    }

    positionalArgumentDescription &operator=(const int &narg) {
        testVal(narg);
        return *this;
    }

    int value() const {
        return pargs;
    }

    bool isSet() const {
        return pargs >= -1;
    };
};