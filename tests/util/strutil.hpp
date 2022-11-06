#pragma once

#include <string>
#include <vector>

namespace riemann {
    [[nodiscard]] std::vector<std::string> split(const std::string &input, char delim);

    [[nodiscard]] std::string trim(std::string_view original);

    bool is_disallowed_character(const char c);
} // namespace riemann


