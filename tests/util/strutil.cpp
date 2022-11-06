#include "strutil.hpp"

namespace riemann {
    std::vector<std::string> split(const std::string &input, char delim) {
        std::size_t current, previous = 0;
        std::vector<std::string> output;
        current = input.find(delim);
        while (current != std::string::npos) {//split autors when ','
            output.push_back(input.substr(previous, current - previous));
            previous = current + 1;
            current = input.find(delim, previous);
        }
        output.push_back(input.substr(previous, current - previous));
        return output;
    }

    static std::string FORBIDDEN_CHARS = ",";

    bool is_disallowed_character(const char c) {
        return std::isspace(c) || FORBIDDEN_CHARS.find(c) != std::string::npos;
    }

    std::string trim(std::string_view original) {
        auto n = original.size();
        size_t begin, end;
        for (begin = 0; begin < n && is_disallowed_character(original[begin]); begin++) { ; }

        for (end = n - 1; end > begin && is_disallowed_character(original[end]); end--) { ; }
        if (end < begin)
            return "";

        return std::string(original.substr(begin, end - begin + 1));

    }

}