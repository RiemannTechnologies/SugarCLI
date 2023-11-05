//
// Created by thonkdifferent on 05.11.2023.
//

#pragma once
#include <vector>
#include <string>
namespace Sugar::CLI {
    struct string_convertor{

        std::vector<std::string> to_string_array(size_t n, char **pString) noexcept {
            std::vector<std::string> result;
            for(int i = 0; i<n; i++)
            {
                result.emplace_back(pString[i]);
            }
            result.shrink_to_fit();
            return result;
        }
    };
}
