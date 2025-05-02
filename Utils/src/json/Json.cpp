#include "json/Json.h"

namespace r_utils
{
    namespace json
    {
        Json::Json(r_utils::json::JsonObject obj)
            : obj(obj) {}

        r_utils::json::JsonElement Json::parse(const std::string& input)
        {
            return r_utils::json::JsonParser().parse(input);
        }

        r_utils::json::JsonElement Json::parse(const r_utils::io::File& file)
        {
            return r_utils::json::JsonParser().parse(file);
        }


        r_utils::json::JsonObject Json::emptyObject()
        {
            return r_utils::json::JsonObject();
        }

        std::string Json::toString()
        {
            return this->obj.toString();
        }
    }
}
