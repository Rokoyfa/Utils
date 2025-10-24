[README.md](../README.md)
# 🧾 Logger Utilities

> A modern, lightweight, and colorful logging utility for C++ — designed for clarity, flexibility, and simplicity.

---

## ✨ Overview

The **RUtils Logger** provides a simple yet powerful way to handle logging in C++ applications.  
It supports multiple log levels (Info, Debug, Warn, Error, etc.), ANSI color output, timestamps, and predefined error types.

The logger is ideal for developers who want structured and visually clear console output without relying on heavy dependencies.

---

## 🚀 Key Features

✅ **Multiple Log Levels:** `LOG`, `INFO`, `DEBUG`, `WARN`, `ERR`  
✅ **Color-coded Output:** Easily distinguish log severity  
✅ **Timestamps:** Every log is tagged with the current date and time  
✅ **Predefined Error Types:** Quickly identify common runtime or system errors  
✅ **Cross-Platform:** Works on Windows, Linux, and macOS  
✅ **Lightweight:** No external dependencies — pure standard C++  
✅ **Macros Included:** Simplified syntax for clean, readable code  

---

## 🧠 Why This Logger?

Unlike basic `std::cout` logging, the **RUtils Logger** gives structure and style to your output.  
It’s perfect for debugging, runtime diagnostics, or even production logs.  

Here’s what makes it shine:

- 🧩 **Modular Design:** Part of the RUtils framework, easily extendable  
- 🖌️ **Readable Output:** Colors and timestamps help spot important messages fast  
- ⚡ **Macros:** Simple one-liners for clean, consistent usage  
- 🪶 **Lightweight:** No external libraries, minimal overhead  

---

## 🧩 Usage Example

### 🔹 Basic Setup

```cpp
#include "logger/Logger.h"
using namespace r_utils::logger;

int main() {
    Logger log;
    log.enableColors(true); // Enable color output (optional)

    log.log("Starting system...");
    log.info("Initialization successful.");
    log.debug("Loading configuration...");
    log.warn("Low disk space detected!");
    log.error("Unable to connect to database.", ErrorType::DATABASE_ERROR);

    return 0;
}
```

🖥️ **Output Example:**
```
[2025-10-24 12:34:56] [LOG] Starting system...
[2025-10-24 12:34:56] [INFO] Initialization successful.
[2025-10-24 12:34:56] [DEBUG] Loading configuration...
[2025-10-24 12:34:56] [WARN] Low disk space detected!
[2025-10-24 12:34:56] [ERROR 1006] Unable to connect to database.
```

---

## 🧰 Using Macros

For even simpler and cleaner logging, use the provided macros:

```cpp
#include "LoggerMacros.h"
using namespace r_utils::logger;

int main() {
    Logger* logger = new Logger();
    logger->enableColors(true);

    LOG_INFO(logger, "Application started");
    LOG_DEBUG(logger, "Debugging enabled");
    LOG_WARN(logger, "High memory usage detected");
    LOG_ERROR(logger, "Database unreachable", ErrorType::DATABASE_ERROR);
    LOG_LOG(logger, "Normal log entry");

    delete logger;
    return 0;
}
```

🧩 **Benefits of Macros:**
- Compact syntax  
- Safe null-pointer handling  
- Consistent logging structure  

---

## ⚙️ Predefined Error Types

The logger comes with a wide range of **predefined `ErrorType` enums**, such as:

| Error Type | Code | Description |
|-------------|------|-------------|
| `FILE_NOT_FOUND` | 404 | The requested file could not be located |
| `NETWORK_ERROR` | 503 | Network communication failure |
| `INVALID_INPUT` | 1001 | Provided input is malformed |
| `DATABASE_ERROR` | 1006 | Error during database operation |
| `OUT_OF_MEMORY` | 1003 | Memory allocation failure |
| `TIMEOUT` | 1004 | Operation exceeded allowed time |
| `RUNTIME_ERROR` | 2000 | General runtime exception |

…and many more!

---

## 🧪 Example: ErrorType in Use

```cpp
log.error("Configuration file missing!", ErrorType::FILE_NOT_FOUND);
log.error("Authentication failed.", ErrorType::AUTHENTICATION_FAILED);
```

🧠 Helps categorize and identify recurring issues easily.

---

## 🖌️ Customization

You can fully control console color output:

```cpp
log.enableColors(false); // Disable colored output
```

If colors are disabled, logs will still include timestamps and severity labels.

---

## 🧩 Integration Tip

This logger fits perfectly into:
- 🧱 **Backend systems**
- 💾 **File or Database applications**
- 🧪 **Debug builds**
- 🕹️ **Game engines or tools**
- ⚙️ **Custom frameworks like RUtils**

---

## 🧩 File Overview

| File | Description |
|------|--------------|
| `Logger.h` | Logger class definition and enums |
| `Logger.cpp` | Implementation of logging methods |
| `LoggerMacros.h` | Helper macros for concise logging |

---

## 🏁 Summary

> The RUtils Logger brings clarity and structure to your C++ console output.  
> Designed with modern standards, cross-platform support, and minimal dependencies in mind — it’s the perfect fit for professional projects and hobby coding alike.

---

### 💡 Tip:
Combine the `Logger` with other RUtils modules like **Timer** and **Event** for a fully-featured developer toolkit!

---

📦 **Namespace:** `r_utils::logger`
👤 **Author:** Rokoyfa  
🕓 **Last Updated:** October 2025
