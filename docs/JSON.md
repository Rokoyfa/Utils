[README](../README.md)
# 🧩 JSON Utilities — `JsonElement`, `JsonArray`, `JsonObject`, `JsonParser`

This document describes the **JSON utility system** in the **RUtils** framework.
It provides a lightweight and intuitive API to parse, manipulate, and serialize JSON data — fully implemented in modern C++.

---

## 🔹 Overview

### 🧱 Components

| Class | Description |
|-------|--------------|
| **JsonElement** | Represents a single JSON value (string, number, boolean, null, array, or object). |
| **JsonArray** | Dynamic list of `JsonElement` values. |
| **JsonObject** | Key-value map storing JSON elements, similar to a dictionary. |
| **JsonParser** | Converts between JSON strings and object representations. |

All classes are located in:
```
Utils/include/json/
Utils/src/json/
```

---

## ⚙️ Core Class: JsonElement

`r_utils::json::JsonElement` is the universal wrapper for any JSON type.

### 🧩 Features

* Supports all JSON types
* Type-safe getters (e.g., `asInt()`, `asString()`)
* Deep copy and equality comparison
* Conversion to string

### 💡 Example

```cpp
r_utils::json::JsonElement value("Hello World");
std::cout << value.asString(); // "Hello World"
```

### 🔧 Supported Types

| Enum | Description |
|------|--------------|
| `JsonType::Null` | Represents JSON null |
| `JsonType::String` | UTF-8 text value |
| `JsonType::Int` | 64-bit integer |
| `JsonType::Double` | Floating-point number |
| `JsonType::Boolean` | true/false |
| `JsonType::Array` | `JsonArray` instance |
| `JsonType::Object` | `JsonObject` instance |

---

## 📜 JsonArray

`r_utils::json::JsonArray` represents a dynamic list of elements.

### 🧩 Features

* Add, access, and remove elements by index
* Iteration with STL-style syntax
* Conversion to JSON string
* Comparison and cloning

### 💡 Example

```cpp
r_utils::json::JsonArray arr;
arr.add(42);
arr.add("Text");
arr.add(true);

std::cout << arr.toString(); // [42, "Text", true]
```

---

## 🗂️ JsonObject

`r_utils::json::JsonObject` is a key-value storage for `JsonElement`s.

### 🧩 Features

* Add or update elements with `set()`
* Access via `get()` or `operator[]`
* Pretty-printing with indentation
* Type-safe conversion from/to JSON string
* Recursive serialization for nested objects/arrays

### 💡 Example

```cpp
r_utils::json::JsonObject obj;
obj.set("name", "Bro");
obj.set("age", 21);
obj.set("languages", r_utils::json::JsonArray({"C++", "Java", "Python"}));

std::cout << obj.toString(true); // pretty printed JSON
```

### 🔁 toString() Example Output

```json
{
  "name": "Bro",
  "age": 21,
  "languages": ["C++", "Java", "Python"]
}
```

---

## 🧠 JsonParser

`r_utils::json::JsonParser` converts between strings and JSON objects or arrays.

### 🧩 Features

* Parse JSON string into `JsonObject` or `JsonArray`
* Handle nested data structures
* Type detection for numbers, strings, booleans, null
* Error handling for malformed input

### 💡 Example

```cpp
auto obj = r_utils::json::JsonParser::parseObject(R"({
    "username": "Bro",
    "active": true,
    "score": 1337
})");

std::cout << obj.get("username").asString(); // Bro
```

---

## ⚙️ Integration Example

### Full JSON workflow

```cpp
#include "json/JsonParser.h"
#include <iostream>

int main() {
    using namespace r_utils::json;

    // Parse from string
    auto obj = JsonParser::parseObject(R"({"user":"Bro","xp":1500})");

    // Modify data
    obj.set("xp", obj.get("xp").asInt() + 500);

    // Add new key
    obj.set("rank", "Elite");

    // Print back to string
    std::cout << obj.toString(true) << std::endl;
}
```

Output:
```json
{
  "user": "Bro",
  "xp": 2000,
  "rank": "Elite"
}
```

---

## 🧾 Summary

| Class | Responsibility |
|--------|----------------|
| `JsonElement` | Core data holder for any JSON value |
| `JsonArray` | Ordered list of JSON elements |
| `JsonObject` | Key-value structure for JSON objects |
| `JsonParser` | Responsible for parsing and string conversion |

---

## ⚠️ Notes

* Thread-safety is **not** guaranteed — use external synchronization if needed.
* Designed for **simplicity and readability**, not for high-performance parsing.
* Compatible with modern C++17+ compilers.

---

📚 **Next Steps**
* Explore the `tests/json/` folder for full usage demos.
* Combine with `FileUtils` to load JSON files directly from disk.

---

📦 **Namespace:** `r_utils::json`
👤 **Author:** Rokoyfa  
🕓 **Last Updated:** October 2025 
