# Installation Instructions for Utils

This document provides detailed instructions on how to integrate the `Utils` C++ library into your projects, including using it as a plugin.

## Prerequisites

* A C++ compiler that supports C++17 or later.
* A build system (e.g., CMake, Make, Visual Studio Project).

## Integrating Utils into Your Project

There are several ways to integrate `Utils` depending on your project's build system and how you manage dependencies.

### 1. Manual Integration (Header-Only or with Pre-built Libraries)

   * **Header-Only (if applicable):**
        1.  **Clone the Repository:**
            ```bash
            git clone [https://github.com/Rokoyfa/Utils]
            ```
        2.  **Include Directory:** Add the `include` directory (located at `Utils/include` in the repository, assuming this structure) to your project's compiler include paths.

            * **Example (g++):** Use the `-I/path/to/your/project/Utils/include` flag during compilation.
            * **Example (Visual Studio):** Add the directory to the "Additional Include Directories" in your project's properties.

        3.  **Include Headers in Your Code:**
            ```cpp
            #include "io/File.h"
            #include "json/Json.h"
            #include "json/JsonObject.h"
            // Or:
            #include "Utils/all.h" // If you use the all.h header
            ```

   * **With Pre-built Libraries (if provided):**
        1.  **Clone the Repository:** (as above)
        2.  **Include Directory:** Add the `include` directory to your compiler include paths (as above).
        3.  **Link Libraries:** Link against the pre-built library files (`.lib` on Windows, `.so` or `.a` on Linux/macOS). You'll need to add the directory containing the libraries to your linker paths and specify the library names in your linker settings.

            * **Example (g++):** Use `-L/path/to/your/libraries` and `-lutils` (assuming your library is named `libutils.so` or `libutils.a`).
            * **Example (Visual Studio):** Add the library directory to "Additional Library Directories" and the library file name to "Additional Dependencies" in your project's linker settings.

### 2. Integration with CMake

   If your project uses CMake, and `Utils` provides a `CMakeLists.txt`, you can integrate it using `find_package` or `add_subdirectory`:

   * **Using `find_package` (if `Utils` is installed or provides a config file):**
        ```cmake
        find_package(Utils CONFIG REQUIRED)
        target_link_libraries(your_target Utils::utils)
        ```
        Ensure that CMake can find the `Utils` package (e.g., by setting `CMAKE_PREFIX_PATH` or installing `Utils` to a standard location).

   * **Using `add_subdirectory` (if `Utils` is within your project source):**
        1.  Place the `Utils` repository (or a copy of it) within your project's source tree.
        2.  Add the following to your main `CMakeLists.txt`:
            ```cmake
            add_subdirectory(Utils)
            target_link_libraries(your_target Utils::utils)
            target_include_directories(your_target PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/Utils/include)
            ```
        3.  In your source files:
            ```cpp
            #include "io/File.h"
            #include "json/Json.h"
            #include "json/JsonObject.h"
            ```

### 3. Using Utils as a Plugin

   The process of using `Utils` as a plugin depends heavily on the specific plugin system of the host application. Generally, you will need to:

   1.  **Obtain the `Utils` library:** This might involve cloning the repository or obtaining pre-built binaries.
   2.  **Include Headers:** Ensure that the `include` directory of `Utils` is in the include paths used by the plugin development kit or the host application's build system.
   3.  **Link Library:** Link your plugin against the `Utils` library (if it's a dynamically linked library). The way this is done is specific to the plugin system.
   4.  **Package Plugin:** Package your plugin according to the host application's requirements, ensuring that the `Utils` library (if dynamically linked) is either bundled with the plugin or is expected to be available in the host environment.

   **Consult the documentation of the specific application you are developing a plugin for to understand the exact steps required for including external libraries.**

By separating the detailed installation instructions into `INSTALL.md`, your main `README.md` remains concise and focused on the library's overview and features. Remember to create the `INSTALL.md` file in the root of your repository alongside `README.md`.