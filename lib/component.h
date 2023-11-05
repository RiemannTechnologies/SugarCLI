#pragma once
#include "SugarInput/lib/IOStreamable.h"
#include "item.h"
namespace Sugar::CLI {
    struct component{

        std::vector <abstract_item* > db;
        template<Input::IOStreamable T>
        void register_item(item<T>* item)
        {
            db.emplace_back(item);
        }

        [[nodiscard]] const std::vector<abstract_item *> &advertise_items() const {
            return db;
        }

        virtual int run() = 0;
    };
}
