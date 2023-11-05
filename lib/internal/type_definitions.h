#pragma once

#include <map>
#include <vector>
#include <string>

namespace Sugar::CLI {
    using vmap = std::map<std::string, std::vector<std::string>>;
    using argv_t = std::vector<std::string>;
}
