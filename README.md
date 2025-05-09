# Utils - 

`Utils` is a C++ library providing a collection of reusable utility classes and functions. It currently includes modules for basic file operations and JSON data handling.
`Utils` is designed to reduce boilerplate code in modern C++ projects.

## Current Features

### `r_utils` - Main namespace for all modules and classes

### `r_utils::io` - File Utilities

This module offers a `File` class for simple file operations:

* **File Creation:** Allows for the creation of new files.
* **Existence Check:** Checks if a file exists at the specified path.
* **File Reading:** Reads the entire content of a text file as a `std::string`.
* **File Writing:** Writes a `std::string` to a file (overwrites existing content).
* **File Appending:** Appends a `std::string` to the end of an existing file.
* **File Removal:** Deletes a file from the file system.
* **Get File Path:** Returns the current file path of the `File` object.

### `r_utils::json` – JSON Handling

This module provides essential classes for parsing, constructing, and serializing JSON data in C++.

- **`r_utils::json::JsonType`**  
  Enum class representing possible JSON types like `Null`, `String`, `Int`, `Double`, `Boolean`, `Object`, and `Array`.

- **`r_utils::json::Json`**  
  Represents a single JSON value and provides methods for type checking, value access, and serialization.

- **`r_utils::json::JsonObject`**  
  A key-value mapping structure for JSON objects, allowing retrieval, insertion, removal, and serialization of properties.

- **`r_utils::json::JsonArray`**  
  A list-based structure for handling JSON arrays with support for appending, accessing elements, and converting to string.

- **`r_utils::json::JsonParser`**  
  Static utility class that parses JSON strings into `JsonObject` or `JsonArray` instances.



## Next Steps

1. **Code Cleanup & Error Handling:**
   - Refactor and restructure code to improve maintainability and readability.
   - Introduce debug logging for key operations and edge cases.
   - Add proper error handling (e.g., invalid file paths, malformed JSON, access errors).

## Installation

1. **Clone the Repository:**
    ```bash
    git clone [your_repository_url_here]
    ```

2. **Compilation:**
    Depending on whether your library is header-only or has separate source files, the compilation process will vary. For a project with separate `.cpp` files, an example using g++ is:
    ```bash
    g++ -c src/io/File.cpp -o build/File.o
    g++ -c src/json/Json.cpp -o build/Json.o
    g++ -c src/json/JsonObject.cpp -o build/JsonObject.o
    g++ main.cpp build/File.o build/Json.o build/JsonObject.o -o utils_app
    ```
    (Adjust the paths and compilation command according to your project structure and build system.)

3. **Include:**
    In your C++ source files, include the necessary header files:
    ```cpp
    #include "Utils/io/File.h"
    #include "Utils/json/Json.h"
    #include "Utils/json/JsonObject.h"
    ```
    Or just do:
    ```cpp
    #include "Utils/all.h"
    ```
    to include all files.

    For further and detailed installation instructions, including how to integrate `Utils` into your project and as a plugin, please refer to the [INSTALL.md](INSTALL.md) file. 
    (Adjust the include paths according to your project structure.)

## Usage

### File (r_utils::io::File)
```cpp
#include <iostream>
#include "file/File.h"

int main()
{
	
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
		// console output: "Hello World!"

		test.append(" Apended output");

		std::cout << test.read() << "\n";
		// console output: "Hello World! Apended output"
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
```

### JsonElement (r_utils::io::JsonElement)
```cpp
#include <iostream>
#include "json/JsonElement.h"

int main()
{
	r_utils::json::JsonElement element = r_utils::json::JsonElement(std::string("Hello"));
	
	try
	{
		std::cout << element.getType() << std::endl;
		// console output: "String"

		if (!element.isString())
		{
			throw std::runtime_error("element is not a String");
		}

		std::string str = element.asString();

		std::cout << str << std::endl;
		//console output: "Hello"
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
```
- Also usable with JsonObject, JsonArray, Boolean, Integer, Double and Null.

### JsonObject (r_utils::io::JsonObject)
```cpp
#include <iostream>
#include "json/JsonObject.h"
#include "json/JsonElement.h"

int main()
{
	r_utils::json::JsonObject obj = r_utils::json::JsonObject();
	
	try
	{
		// Simple JsonObject

		obj.set("name", r_utils::json::JsonElement(std::string("Name1")));
		obj.set("age", r_utils::json::JsonElement(18));

		std::cout << obj.get("name").asString() << std::endl;
		// console output: "Name1"

		std::cout << obj.toString() << std::endl;
		// console output: "{"name":"Name1","age":18}"


		// Nested JsonObjects
		r_utils::json::JsonObject dog = r_utils::json::JsonObject()
			.set("name", r_utils::json::JsonElement(std::string("Bello")))
			.set("age", r_utils::json::JsonElement(8))
			.set("race", r_utils::json::JsonElement(std::string("Shepherd")));

		r_utils::json::JsonObject cat = r_utils::json::JsonObject()
			.set("name", r_utils::json::JsonElement(std::string("nemo")))
			.set("age", r_utils::json::JsonElement(3))
			.set("color", r_utils::json::JsonElement(std::string("Black")));

		r_utils::json::JsonObject pets = r_utils::json::JsonObject()
			.set("bello", dog)
			.set("nemo", cat);

		obj.set("pets", pets);

		std::cout << obj.get("pets").asObject() << std::endl;
		// console output: "{"bello":{"name":"Bello","age":8,"race":"Shepherd"},"nemo":{"name":"nemo","age":3,"color":"Black"}}"
		
		r_utils::json::JsonObject obj2 = obj.get("pets").asObject();

		std::cout << obj2.get("bello").asObject() << std::endl;
		// console output: "{"name":"Bello","age":8,"race":"Shepherd"}"

		std::cout << obj.toString(true) << std::endl;
		/* console output:
		*{
			"name": "Name1",
			"age": 18,
			"pets": {
				    "bello": {
					        "name": "Bello",
						    "age": 8,
							"race": "Shepherd"
					},
					"nemo": {
						    "name": "nemo",
							"age": 3,
							"color": "Black"
					}
			}
		*}
		*/
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
```

### JsonArray  (r_utils::io::JsonArray )
```cpp
#include <iostream>
#include "json/JsonArray.h"
#include "json/JsonElement.h"

int main()
{
	r_utils::json::JsonArray arr;

	/*
	* Optional:
		r_utils::json::JsonArray arr = r_utils::json::JsonArray()
			.add(r_utils::json::JsonElement(std::string("This")))
			.add(r_utils::json::JsonElement(std::string("is")))
			.add(r_utils::json::JsonElement(std::string("a")))
			.add(r_utils::json::JsonElement(std::string("Array")))
			.add(r_utils::json::JsonElement(std::string("Pong")));
	*/
	
	try
	{
		arr.add(r_utils::json::JsonElement(std::string("This")));
		arr.add(r_utils::json::JsonElement(std::string("is")));
		arr.add(r_utils::json::JsonElement(std::string("a")));
		arr.add(r_utils::json::JsonElement(std::string("Array")));
		arr.add(r_utils::json::JsonElement(std::string("Pong")));

		std::cout << arr << std::endl;
		// console output: ["This","is","a","Array","Pong"]

		arr.remove(r_utils::json::JsonElement(std::string("Pong")));

		std::cout << arr << std::endl;
		// console output: ["This","is","a","Array"]
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
```

### JsonParser (r_utils::io::JsonParser)
```cpp
#include "Utils/json/JsonParser.h"
#include <iostream>

int main() {
    #include <iostream>
#include <string>
#include "json/JsonParser.h"
#include "json/JsonObject.h"
#include "json/JsonElement.h"
#include "json/JsonArray.h"

int main() {
    try {
        std::string jsonString = R"({"name": "John Doe", "age": 30, "isStudent": false, "courses": ["Math", "Science"], "address": {"street": "123 Main St", "city": "Anytown"}})";

        std::cout << "JSON string to be parsed:\n" << jsonString << std::endl;

        r_utils::json::JsonObject jsonObject = r_utils::json::JsonParser::parse(jsonString);

        std::cout << "\nSuccessfully parsed JsonObject:\n" << jsonObject.toString(true) << std::endl; // Use toString with prettyPrint for better readability

        // Accessing individual elements
        std::cout << "\nAccessing individual elements:" << std::endl;
        if (jsonObject.contains("name")) {
            std::cout << "Name: " << jsonObject.get("name").asString() << std::endl;
        }
        if (jsonObject.contains("age")) {
            std::cout << "Age: " << jsonObject.get("age").asDouble() << std::endl;
        }
        if (jsonObject.contains("isStudent")) {
            std::cout << "Is Student: " << (jsonObject.get("isStudent").asBoolean() ? "true" : "false") << std::endl;
        }
        if (jsonObject.contains("courses")) {
            r_utils::json::JsonArray courses = jsonObject.get("courses").asArray();
            std::cout << "Courses: " << courses << std::endl;
        }
        if (jsonObject.contains("address")) {
            r_utils::json::JsonObject address = jsonObject.get("address").asObject();
            if (address.contains("street")) {
                std::cout << "Address - Street: " << address.get("street").asString() << std::endl;
            }
            if (address.contains("city")) {
                std::cout << "Address - City: " << address.get("city").asString() << std::endl;
            }
        }

        // Example of an error case (invalid JSON)
        std::string invalidJsonString = "{ \"name\": \"Jane Doe\", \"age\": }";
        std::cout << "\nAttempting to parse invalid JSON:\n" << invalidJsonString << std::endl;
        r_utils::json::JsonObject invalidJsonObject = r_utils::json::JsonParser::parse(invalidJsonString);
        std::cout << "Should not reach here!" << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "\nError parsing JSON data: " << e.what() << std::endl;
    }

    return 0;
}
}
```

### Example of use
```cpp
#include <iostream>
#include <string>
#include "json/JsonParser.h"
#include "json/JsonObject.h"
#include "json/JsonElement.h"
#include "json/JsonArray.h"
#include "json/Json.h"
#include "file/File.h"

int main() {
    try {
        // Path to the JSON file
        std::string filePath = "storage/storage.json";
        r_utils::io::File jsonFile(filePath);

        std::cout << "Attempting to read JSON data from file: " << jsonFile.getFilePath() << std::endl;

        // Read JSON data from the file
        std::string jsonString = jsonFile.read();
        std::cout << "Successfully read JSON content:\n" << jsonString << std::endl;

        // Parse the JSON data
        r_utils::json::JsonObject rootObject = r_utils::json::JsonParser::parse(jsonString);

        std::cout << "\nSuccessfully parsed JSON object:\n" << rootObject.toString(true) << std::endl;

        // Example operations on the parsed data
        if (rootObject.contains("users") && rootObject.get("users").isArray()) {
            r_utils::json::JsonArray usersArray = rootObject.get("users").asArray();
            std::cout << "\nIterating through users:" << std::endl;
            for (size_t i = 0; i < usersArray.size(); ++i) {
                if (usersArray.getValues()[i].isObject()) {
                    r_utils::json::JsonObject userObject = usersArray.getValues()[i].asObject();
                    if (userObject.contains("username") && userObject.contains("email")) {
                        std::cout << "- Username: " << userObject.get("username").asString()
                            << ", Email: " << userObject.get("email").asString() << std::endl;
                    }
                }
            }

            // Example of adding a new element (assuming you have a method to modify JsonObject/JsonArray)
            // Here, only the string representation is created for output
            r_utils::json::JsonObject newUser;
            newUser.set("username", r_utils::json::JsonElement("new_user"));
            newUser.set("email", r_utils::json::JsonElement("new@example.com"));

            // Add the new user object (as a string) to the output
            std::stringstream updatedJsonStream;
            updatedJsonStream << rootObject.toString(true).substr(0, rootObject.toString(true).size() - 2) // Remove last "}"
                << ",\n  \"newUser\": " << newUser.toJson().toString() << "\n}";
            std::cout << "\nExample of adding a new element (output string):\n" << updatedJsonStream.str() << std::endl;

            // Convert the modified JsonObject back to a JSON string and write it to the file
            r_utils::json::Json jsonWrapper = rootObject.toJson();
            std::string updatedJsonString = jsonWrapper.toString();
            jsonFile.write(updatedJsonString);

            std::cout << "\nUpdated JSON written back to " << jsonFile.getFilePath() << std::endl;
        }
        else {
            std::cout << "\n'users' array not found in the JSON data." << std::endl;
        }

    }
    catch (const std::exception& e) {
        std::cerr << "\nError during application execution: " << e.what() << std::endl;
    }

    return 0;
}
```

## License

This project is licensed under the [MIT License](LICENSE). See the [LICENSE](LICENSE) file for more information.

## Copyright

Copyright (c) 2025 Rokoyfa
