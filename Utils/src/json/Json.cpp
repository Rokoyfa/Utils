#include "json/Json.h"

namespace r_utils
{
    namespace json
    {

        r_utils::json::JsonElement Json::parse(const std::string& input)
        {
            return r_utils::json::JsonElement();
        }


        std::string Json::stringify(const r_utils::json::JsonElement& element)
        {
            return std::string();
        }


        r_utils::json::JsonObject Json::emptyObject()
        {
            return r_utils::json::JsonObject();
        }
    }
}
