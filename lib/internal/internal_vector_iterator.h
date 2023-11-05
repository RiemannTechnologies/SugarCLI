#pragma once
#include <string>
#include <vector>
namespace Sugar::CLI{
    struct internal_vector_iterator {

        int index = 0;
        std::vector<std::string> array;
        explicit internal_vector_iterator(std::vector<std::string> vector) : array(std::move(vector))
        {}

        [[nodiscard]] bool can_continue() const
        {
            return index < array.size()-1;
        }
        internal_vector_iterator next()
        {
            if(!can_continue()) return *this;
            internal_vector_iterator new_iterator = *this;
            new_iterator.index = this->index+1;
            return new_iterator;
        }
        [[nodiscard]] std::string value() const
        {
            return array[index];
        }
    };
}