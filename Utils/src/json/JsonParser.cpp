#include "json/JsonParser.h"

#include "exception/json/JsonParserException.h"

namespace r_utils
{
	namespace json
	{

		JsonElement JsonParser::parse(const std::string& input)
		{
			JsonParser parser(input);
			return parser.parseValue();
		}

		JsonElement JsonParser::parse(const r_utils::io::File& file)
		{
			if (!file.exists())
			{
				throw r_utils::exception::JsonParserException("Failed to Parse file: " + file.getFilePath());
			}
			return parse(file.read().c_str());
		}


		JsonParser::JsonParser(std::string input)
			: input(input), pos(0) {}


		char JsonParser::peek() const
		{
			return pos < input.size() ? input[pos] : '\0';
		}

		char JsonParser::next()
		{
			return pos < input.size() ? input[pos++] : '\0';
		}

		bool JsonParser::eof() const
		{
			return pos >= input.size();
		}

		void JsonParser::skipWhitespace()
		{
			while (!eof() && std::isspace(static_cast<unsigned char>(peek()))) {
				next();
			}
		}

		JsonElement JsonParser::parseValue()
		{
			skipWhitespace();
			char c = peek();

			if (c == 'n') return parseNull();
			if (c == 't' || c == 'f') return parseBool();
			if (c == '"' || c == '\'') return parseString();
			if ((c >= '0' && c <= '9') || c == '-' || c == '+') return parseNumber();
			if (c == '{') return parseObject();
			if (c == '[') return parseArray();

			throw r_utils::exception::JsonParserException("Unexpected token: " + std::string(1, c));
		}

		JsonElement JsonParser::parseNull()
		{
			if (input.substr(pos, 4) == "null") {
				pos += 4;
				return JsonElement(nullptr);
			}
			throw r_utils::exception::JsonParserException("Invalid null value");
		}

		JsonElement JsonParser::parseBool()
		{
			if (input.substr(pos, 4) == "true") {
				pos += 4;
				return JsonElement(true);
			}
			else if (input.substr(pos, 5) == "false") {
				pos += 5;
				return JsonElement(false);
			}
			throw r_utils::exception::JsonParserException("Invalid boolean value");
		}

		JsonElement JsonParser::parseNumber()
		{
			size_t start = pos;
			if (peek() == '-') next();
			while (std::isdigit(peek())) next();
			if (peek() == '.') {
				next();
				while (std::isdigit(peek())) next();
			}
			std::string numStr = std::string(input.substr(start, pos - start));
			return JsonElement(std::stod(numStr));
		}

		JsonElement JsonParser::parseString()
		{
			char quote = next();
			std::string result;
			while (!eof()) {
				char c = next();
				if (c == quote) break;
				if (c == '\\') {
					char esc = next();
					switch (esc) {
					case 'n': result += '\n'; break;
					case 't': result += '\t'; break;
					case '\\': result += '\\'; break;
					case '"': result += '"'; break;
					case '\'': result += '\''; break;
					default: result += esc; break;
					}
				}
				else {
					result += c;
				}
			}
			return JsonElement(result);
		}

		JsonArray JsonParser::parseArray()
		{
			JsonArray array;

			if (next() != '[')
				throw r_utils::exception::JsonParserException("Expected '[' to start array");

			skipWhitespace();
			if (peek() == ']') {
				next();
				return array;
			}

			while (!eof()) {
				skipWhitespace();
				JsonElement element = parseValue();
				array.add(element);

				skipWhitespace();
				if (eof())
					throw r_utils::exception::JsonParserException("Unexpected end of input in array");

				char ch = next();
				if (ch == ']') {
					break;
				}
				else if (ch != ',') {
					throw r_utils::exception::JsonParserException("Expected ',' or ']' in array, got '" + std::string(1, ch) + "'");
				}
			}

			return array;
		}

		JsonObject JsonParser::parseObject()
		{
			JsonObject obj;

			if (next() != '{') {
				throw r_utils::exception::JsonParserException("Expected '{'");
			}

			skipWhitespace();
			if (peek() == '}') {
				next();
				return obj;
			}

			while (!eof()) {
				skipWhitespace();
				auto keyElement = parseString();
				std::string key = keyElement.asString();

				skipWhitespace();
				if (next() != ':') {
					throw r_utils::exception::JsonParserException("Expected ':' after key");
				}

				skipWhitespace();
				JsonElement value = parseValue();

				obj.set(key, value);

				skipWhitespace();
				if (peek() == ',') {
					next();
					continue;
				}
				if (peek() == '}') {
					next();
					break;
				}
				throw r_utils::exception::JsonParserException("Expected ',' or '}' in object");
			}

			return obj;
		}
	} // json
} // r_utils
