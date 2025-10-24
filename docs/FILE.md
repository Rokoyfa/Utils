[README.md](../README.md)
# 📂 File Utility — `r_utils::io::File`

The `r_utils::io::File` class is a lightweight, convenient wrapper around common filesystem operations, such as checking existence, reading, writing, appending, creating, and removing files. It is designed to simplify everyday file handling in C++ projects.

**Location in the repository:**

* Header: `Utils/include/file/File.h`
* Implementation: `Utils/src/file/File.cpp`

---

## ⚡ Key Features

* **Existence checks** — easily determine if a file exists
* **Read full contents** — load entire file into a `std::string`
* **Write / append** — overwrite or append data to files
* **Create / remove** — safely create or delete files
* **Exception-safe** — all errors throw `r_utils::exception::FileException`

**Namespace:** `r_utils::io`
**Main exception type:** `r_utils::exception::FileException`

---

## 📝 API Overview

### Constructor

```cpp
File(std::string filePath)
```

* **Input:** Path to the file (`std::string`). Must not be empty.
* **Throws:** `FileException` if the path is empty.

### Member Functions

| Function                                  | Description                                          | Throws                                   |
| ----------------------------------------- | ---------------------------------------------------- | ---------------------------------------- |
| `bool exists()`                           | Returns `true` if the file exists, `false` otherwise | `FileException` on filesystem error      |
| `std::string read()`                      | Returns the full file contents                       | `FileException` if file cannot be opened |
| `bool write(const std::string& content)`  | Overwrites file with `content`                       | `FileException` on failure               |
| `bool append(const std::string& content)` | Appends `content` to the file                        | `FileException` on failure               |
| `bool create()`                           | Creates a new file or truncates an existing one      | `FileException` if creation fails        |
| `bool remove()`                           | Deletes the file                                     | `FileException` if deletion fails        |

---

## 💡 Usage Examples

All examples below demonstrate basic error handling using `FileException`.

### 1️⃣ Read a file if it exists

```cpp
#include "file/File.h"
#include "exception/file/FileException.h"
#include <iostream>

int main() {
    try {
        r_utils::io::File f("data/config.json");
        if (f.exists()) {
            std::string contents = f.read();
            std::cout << "File contents:\n" << contents << std::endl;
        } else {
            std::cout << "File does not exist: " << f.getFilePath() << std::endl;
        }
    } catch (const r_utils::exception::FileException& e) {
        std::cerr << "File error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
```

Use case: reading configuration files or small datasets.

---

### 2️⃣ Create and overwrite a file

```cpp
#include "file/File.h"
#include "exception/file/FileException.h"
#include <iostream>

int main() {
    try {
        r_utils::io::File f("logs/session.log");
        f.create();               // create or truncate
        f.write("Session started\n");
    } catch (const r_utils::exception::FileException& e) {
        std::cerr << "Cannot write file: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
```

Use case: starting a fresh log file.

---

### 3️⃣ Append to a file

```cpp
#include "file/File.h"
#include "exception/file/FileException.h"
#include <iostream>

int main() {
    try {
        r_utils::io::File f("logs/session.log");
        f.append("New log entry\n");
    } catch (const r_utils::exception::FileException& e) {
        std::cerr << "Append failed: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
```

Use case: add entries without overwriting previous content.

---

### 4️⃣ Remove a file

```cpp
#include "file/File.h"
#include "exception/file/FileException.h"
#include <iostream>

int main() {
    try {
        r_utils::io::File f("temp/output.tmp");
        if (f.exists()) {
            f.remove();
            std::cout << "Removed: " << f.getFilePath() << std::endl;
        }
    } catch (const r_utils::exception::FileException& e) {
        std::cerr << "Remove failed: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
```

Use case: clean up temporary files.

---

## ⚠️ Notes & Best Practices

* **Exception safety:** Always catch `FileException` to handle I/O errors gracefully.
* **File size:** `read()` loads the entire file into memory. Suitable for small to medium files. For very large files, consider streaming.
* **Atomic writes:** `write()` and `append()` are standard `ofstream` operations. For atomic replace semantics, implement a temporary file strategy externally.
* **Thread-safety:** `File` does **not** internally synchronize access. Protect shared paths externally if accessed concurrently.
* **Paths:** Accepts any path supported by `std::filesystem`. On Windows, prefer native separators or `std::filesystem::path`.

---

## 🔗 References

* Implementation: `Utils/include/file/File.h` / `Utils/src/file/File.cpp`
* Related modules: JSON, Logger, Timer (check `docs/` for usage examples)

---

### 💡 Tip:

> Pro Tip: You can integrate this helper class with `Logger` and `JSON` modules for easy logging of configuration files, runtime logs, and serialized objects.

---

📦 **Namespace:** `r_utils::io`
👤 **Author:** Rokoyfa  
🕓 **Last Updated:** October 2025