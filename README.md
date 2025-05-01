# Utils - 

`Utils` is a C++ library providing a collection of reusable utility classes and functions. It currently includes modules for basic file operations and JSON data handling.

## Current Features

### `r_utils` - Main namespace for all modules and classses

### `r_utils::io` - File Utilities

This module offers a `File` class for simple file operations:

* **File Creation:** Allows for the creation of new files.
* **Existence Check:** Checks if a file exists at the specified path.
* **File Reading:** Reads the entire content of a text file as a `std::string`.
* **File Writing:** Writes a `std::string` to a file (overwrites existing content).
* **File Appending:** Appends a `std::string` to the end of an existing file.
* **File Removal:** Deletes a file from the file system.
* **Get File Path:** Returns the current file path of the `File` object.

### `r_utils::json` - JSON Handling

This module provides classes for processing JSON data:

* **`JsonType`:** An `enum class` defining the supported JSON data types (`Null`, `String`, `Int`, `Double`, `Boolean`, `Object`).
* **`Json`:** A class to represent individual JSON values, supporting various data types through `std::variant`. Includes methods for type checking (`is...`), value retrieval (`as...`), and serialization (`toString()`). The output operator `operator<<` is overloaded for outputting `JsonType` via `std::cout`.
* **`JsonObject`:** A class to represent JSON objects as a `std::unordered_map` of `std::string` keys to `Json` values. Offers methods for checking key existence (`contains`), retrieving values (`get`), setting values (`set`), removing keys (`remove`), getting the size (`size`), and serializing the object to a JSON string (`toString()`).

## Next Steps

The next development phase will focus on implementing a **JSON Parser**. This parser will enable loading JSON data from files and `std::string` objects into the `r_utils::json::Json` and `r_utils::json::JsonObject` structures.

## Installation

1.  **Clone the Repository:**
    ```bash
    git clone [your_repository_url_here]
    ```
2.  **Compilation:**
    Depending on whether your library is header-only or has separate source files, the compilation process will vary. For a project with separate `.cpp` files, an example using g++ is:
    ```bash
    g++ -c src/io/File.cpp -o build/File.o
    g++ -c src/json/Json.cpp -o build/Json.o
    g++ -c src/json/JsonObject.cpp -o build/JsonObject.o
    g++ main.cpp build/File.o build/Json.o build/JsonObject.o -o utils_app
    ```
    (Adjust the paths and compilation command according to your project structure and build system.)

3.  **Include:**
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
    to include all files

    For further and detailed installation instructions, including how to integrate `Utils` into your project and as a plugin, please refer to the [INSTALL.md](INSTALL.md) file. 
    (Adjust the include paths according to your project structure.)

## Usage

Here are some basic examples of how to use the classes:

```cpp
#include "Utils/io/File.h"
#include "Utils/json/Json.h"
#include "Utils/json/JsonObject.h"
#include <iostream>
#include <string>

int main() {
    // File Operations
    r_utils::io::File myFile("example.txt");
    if (!myFile.exists()) {
        myFile.create();
        myFile.write("Hello World!");
        std::cout << "File written." << std::endl;
    }
    std::cout << "File content: " << myFile.read() << std::endl;
    myFile.append("\nThis line was appended.");
    std::cout << "File content after append: " << myFile.read() << std::endl;

    // JSON Operations
    r_utils::json::JsonObject obj = r_utils::json::Json().empty()
        .set("name", r_utils::json::Json(std::string("Example")))
        .set("age", r_utils::json::Json(30));
    std::cout << "JSON Object: " << obj.toString() << std::endl;

    // Nested Json
    r_utils::json::JsonObject nested = r_utils::json::Json().empty()
        .set("person", r_utils::json::Json(obj));
    // Overloaded << operator for JsonObjects
    std::cout << "JSON Object: " << nested << std::endl;

    return 0;
}
```

## License

This project is licensed under the [MIT License](LICENSE). See the [LICENSE](LICENSE) file for more information.

## Copyright

Copyright (c) 2025 Rokoyfa
