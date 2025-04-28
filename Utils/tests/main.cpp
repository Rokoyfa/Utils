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

	r_utils::json::JsonObject pet = r_utils::json::Json().empty()
		.set("name", r_utils::json::Json(std::string("Bello")))
		.set("age", r_utils::json::Json(3));

	r_utils::json::JsonObject obj = r_utils::json::Json().empty()
		.set("name", r_utils::json::Json(std::string("Marc")))
		.set("age", r_utils::json::Json(18))
		.set("pet", r_utils::json::Json(pet));

	storage.write(obj.toString());

	std::cout << storage.read() << "\n\n";
	std::cout << obj.toString(true);
	*/
	

	return 0;
}