#pragma once

#include <vector>
#include <map>
#include <string>
#include <memory>

namespace Sugar::CLI{
    struct cli_environment{
        std::vector<std::string> arguments;
    };
}