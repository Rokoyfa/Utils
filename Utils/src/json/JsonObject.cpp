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

        void JsonObject::remove(const std::string& key)
        {
            values.erase(key);
        }


        size_t JsonObject::size() const
        {
            return values.size();
        }

        std::string JsonObject::indent(int level)
        {
            return std::string(level, '\t');
        }


        std::string JsonObject::toString(bool prettyPrint, int indentLevel) const
        {
            std::stringstream result;

            result << "{";
            if (prettyPrint && !values.empty())
            {
                result << "\n";
            }

            size_t counter = 0;
            for (const auto [key, value] : values)
            {
                if (prettyPrint)
                {
                    result << indent(indentLevel + 1);
                }

                result << "\"" << key << "\"";
                if (prettyPrint)
                {
                    result << " ";
                }

                if (value.isObject()) {
                    result << value.asObject().toString(prettyPrint, indentLevel + 1);
                }
                else if (value.isString()) {
                    result << "\"" << value.asString() << "\"";
                }
                else if (value.isInt()) {
                    result << value.asInt();
                }
                else if (value.isDouble()) {
                    result << value.asDouble();
                }
                else if (value.isBoolean()) {
                    result << (value.asBoolean() ? "true" : "false");
                }
                else {
                    result << "null";
                }


                counter++;

                if (counter < this->size())
                {
                    result << ",";
                }

                if (prettyPrint)
                {
                    result << "\n";
                }
            }

            if (prettyPrint && !values.empty())
            {
                result << indent(indentLevel);
            }

            result << "}";

            return result.str();
        }

        r_utils::json::Json JsonObject::toJson() const {
            return r_utils::json::Json(*this);
        }

    }
}
