#include "json/Json.h"

namespace r_utils
{
    namespace json
    {
        Json::Json()
        {
        }

        Json::Json(JsonElement element)
            : root(std::move(element)) 
        {}


        Json Json::parse(const std::string& input)
        {
            return Json(JsonParser::parse(input));
        }

        Json Json::parse(const r_utils::io::File& file)
        {
            return Json(JsonParser::parse(file));
        }


        bool Json::isObject() const
        {
            return root.isObject();
        }

        bool Json::isArray() const
        {
            return root.isArray();
        }


        JsonObject Json::asObject() const
        {
            return root.asObject();
        }

        JsonArray Json::asArray() const
        {
            return root.asArray();
        }


        std::string Json::toString() const
        {
            return root.stringify();
        }


        JsonObject Json::emptyObject()
        {
            return JsonObject();
        }

        JsonArray Json::emptyArray()
        {
            return JsonArray();
        }

    } // json
} // r_utils
