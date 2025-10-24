# 🧩 RUtils — C++ Utility Framework

**RUtils** is a modern, modular, and lightweight **C++20 utility framework** designed to simplify common development tasks across multiple domains such as logging, timing, JSON parsing, file handling, and more. It provides **small, self-contained modules** with clean APIs that can be easily embedded into any project — from small console tools to large backend systems.

---

## 🚀 Features at a Glance

* 🧱 **Modular design** — each component is independent and can be used standalone
* ⚙️ **Header-friendly API** — minimal includes, simple integration
* 🧵 **Thread-safe utilities** — especially in `Logger`, `Timer`, and event-based modules
* 📦 **Cross-platform** — builds cleanly on Windows, Linux, and macOS
* 📖 **Well-documented** — each module has its own documentation file under `docs/`
* 🪶 **No external dependencies** — everything written from scratch in modern C++

---

## 📦 Module Overview

| Module            |       Status      | Description                                                                   | Documentation                                  |
| :---------------- | :---------------: | :---------------------------------------------------------------------------- | :--------------------------------------------- |
| **RUtilsBuilder** |      ✅ Stable     | Base builder for modular initialization and setup                             | [docs/RUtilsBuilder.md](docs/RUtilsBuilder.md) |
| **Logger**        |      ✅ Stable     | Thread-aware logging system with color output and optional GUI integration    | [docs/Logger.md](docs/Logger.md)               |
| **JSON**          |      ✅ Stable     | Lightweight JSON parser and builder (custom implementation, no external libs) | [docs/Json.md](docs/Json.md)                   |
| **File**          |      ✅ Stable     | File utilities for reading, writing, and managing files safely                | [docs/File.md](docs/File.md)                   |
| **Timer / Time**  |      ✅ Stable     | Thread-safe timing and benchmarking utilities                                 | [docs/Timer.md](docs/Timer.md)                 |
| **Event System**  | 🚧 In Development | Event dispatcher and listener abstraction (core implemented, API evolving)    | [docs/Event.md](docs/Event.md)                 |
| **GUI**           |  ⚠️ Experimental  | Runtime log viewer and window abstraction layer (not yet complete)            | [docs/GUI.md](docs/GUI.md)                     |

> ✅ **Stable:** Tested and ready for production
> 🚧 **In Development:** Partially implemented or changing API
> ⚠️ **Experimental:** Functional but unstable, use for testing only

---

## 🧠 Design Philosophy

RUtils follows a few key design principles:

1. **Simplicity First** — APIs are intuitive and avoid unnecessary abstraction.
2. **No Dependencies** — fully self-contained, no `boost`, no external logging or JSON libs.
3. **Extensibility** — each module can be extended without changing core code.
4. **Thread Safety Where Relevant** — modules like `Timer` and `Logger` are fully thread-safe.
5. **Portability** — tested and built under Windows (MSVC), Linux (GCC/Clang), and macOS.

---

## 🧩 Module Summaries

### 🧱 [RUtilsBuilder](docs/RUtilsBuilder.md)

A base module for initializing and managing RUtils components programmatically.
Provides a clean interface to register and access submodules dynamically.

---

### 🧾 [Logger](docs/Logger.md)

A flexible logging framework supporting:

* Colored console output (Info, Debug, Error, Warning)
* Thread-safe logging queues
* Optional GUI-based log viewer
* Configurable output formats and timestamps

Example:

```cpp
r_utils::logger::Logger log;
log.info("Application started");
log.error("An error occurred during initialization");
```

---

### 📜 [JSON](docs/Json.md)

A minimal but powerful JSON parser and writer:

* Parse strings into structured objects
* Build JSON programmatically
* Convert to/from native C++ types

Example:

```cpp
auto json = r_utils::json::Json::parse("{\"name\":\"RUtils\", \"version\":1}");
std::string name = json["name"].asString();
```

---

### 📂 [File](docs/File.md)

Utility class for file operations:

* Read and write files safely
* Create, delete, and manage paths
* Cross-platform support for relative and absolute paths

Example:

```cpp
r_utils::file::File f("data.txt");
f.create();
f.write("Hello, RUtils!");
```

---

### ⏱️ [Timer / Time](docs/Timer.md)

High-precision and thread-safe timing utilities.
Supports:

* Manual or threaded timers
* Elapsed time calculation in multiple units
* Callback-based async timers

Example:

```cpp
r_utils::time::Timer timer;
timer.start();
// ... some work ...
timer.stop();
std::cout << "Elapsed: " << timer.elapsedMilliseconds() << " ms\n";
```

---

### 🎯 [Event System](docs/Event.md)

Lightweight system for decoupled communication between components.
Useful for async architectures or modular backends.

>🧩 API still evolving — not yet stable.

---

### 🪟 [GUI](docs/GUI.md)

Basic window abstraction for GUI-based log viewing or interactive utilities.
Cross-platform foundation for visual extensions.

>⚠️ Currently experimental — not for production.

---

## ⚙️ Building & Installing RUtils

### Installation

Currently, the library can only be used by cloning the repository directly.
For detailed instructions, see [INSTALL.md](docs/INSTALL.md).

```bash
git clone https://github.com/<your-username>/RUtils.git
cd RUtils
```

> CMake support is planned but not yet implemented.
> Requires **C++20** or higher.

### Using Visual Studio

Open the solution:

```
Utils/Utils.sln
```

Build the desired configuration (`Debug` or `Release`).

### Using CMake (planned)

CMake setup will be documented in `INSTALL.md` once implemented.

---

## 🧪 Examples & Documentation

Each module has a dedicated documentation file with usage examples and API notes:

* [RUtilsBuilder](docs/RUtilsBuilder.md)
* [Logger](docs/Logger.md)
* [JSON](docs/Json.md)
* [File](docs/File.md)
* [Timer](docs/Timer.md)
* [Event](docs/Event.md)
* [GUI](docs/GUI.md)

---

## 🧭 Roadmap

| Feature                    | Status         | Notes                                      |
| -------------------------- | -------------- | ------------------------------------------ |
| Event system rewrite       | 🧩 Planned     | More expressive API and type-safe dispatch |
| GUI log window             | 🧪 In progress | Visual runtime log console                 |
| CI/CD integration          | 🔧 Planned     | GitHub Actions or CMake tests              |
| Unit tests for all modules | 🧪 Ongoing     | Using Catch2 or GoogleTest                 |

---

## 🤝 Contributing

Contributions, ideas, and bug reports are welcome!
To contribute:

1. Fork the repository
2. Create a new branch
3. Commit changes with clear messages
4. Open a Pull Request

If you’re working on an unfinished module (like GUI or Event), please discuss the API design first in an issue.

---

## ⚖️ License

This project is released under the **MIT License**.
See [LICENSE](LICENSE) for details.

---

## 📫 Contact

Maintained by Rokoyfa
If you have questions, suggestions, or feedback, feel free to open an issue or discussion.

---

### ❤️ Thank you for using RUtils!

If you like the project, consider giving it a ⭐ on GitHub — it helps visibility an

---

👤 **Author:** Rokoyfa  
🕓 **Last Updated:** October 2025