#include <iostream>

#include "all.h"

int main()
{
	/*
	r_utils::io::File test = r_utils::io::File("storage/test.txt");
	try
	{
		if (!test.exists())
		{
			test.create();
		}
		std::cout << test.getFilePath() << "\n";
		test.write("Hello World!");
		std::cout << test.read() << "\n";
		test.append("\t Nein es heißt Hallo Welt!");
		std::cout << test.read() << "\n";
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	*/

	/*
	r_utils::io::File storage = r_utils::io::File("storage/storage.json");
	if (!storage.exists())
	{
		storage.create();
	}

	r_utils::json::JsonObject pet = r_utils::json::Json().emptyObject()
		.set("name", r_utils::json::Json(std::string("Bello")))
		.set("age", r_utils::json::Json(3));

	r_utils::json::JsonObject obj = r_utils::json::Json().emptyObject()
		.set("name", r_utils::json::Json(std::string("Marc")))
		.set("age", r_utils::json::Json(18))
		.set("pet", r_utils::json::Json(pet));

	storage.write(obj.toString());

	std::cout << storage.read() << "\n\n";
	std::cout << obj.toString(true);
	*/

	std::string raw = "{\"name\":\"Marc\",\"age\":18,\"job\":\"Programmer\",\"langs\":[\"c++\",\"java\",\"py\",\"js\"]}";
	r_utils::io::File file = r_utils::io::File("storage/storage.json");
	try {
		r_utils::json::JsonElement root = r_utils::json::JsonParser().parse(file);
		if (root.isObject()) {
			r_utils::json::JsonObject obj = root.asObject();
			std::cout << obj << std::endl;

			r_utils::json::JsonObject pet = obj.get("pet").asObject();
			std::cout << pet << std::endl;

			r_utils::json::JsonArray arr = obj.get("langs").asArray();
			std::cout << arr << std::endl;
		}
	}
	catch (const std::exception& ex) {
		std::cerr << "Parse Error: " << ex.what() << std::endl;
	}

	return 0;
}