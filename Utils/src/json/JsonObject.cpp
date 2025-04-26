#include "json/JsonObject.h"

namespace r_utils {
    namespace json {

        bool JsonObject::contains(const std::string& key) const {
            return values.find(key) != values.end();
        }

        Json JsonObject::get(const std::string& key) const {
            auto it = values.find(key);
            if (it != values.end()) {
                return it->second;
            }

            throw std::runtime_error("Key not found: " + key);
        }

        r_utils::json::Json JsonObject::get(const int index) const
        {
            if (index >= this->size()) {
                throw std::out_of_range("Index out of bounds");
            }
            auto it = values.begin();
            std::advance(it, index);
            return it->second;
        }



        r_utils::json::JsonObject JsonObject::set(const std::string& key, const Json& value) {
            values[key] = value;
            return *this;
        }


        size_t JsonObject::size() const
        {
            return values.size();
        }

    }
}
