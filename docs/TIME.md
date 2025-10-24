[README.md](../README.md)
# ⏱️ Time Utilities — `Timer` & `TimeUtils`

This document covers the `Timer` and `TimeUtils` helper classes in the **RUtils** framework.
These classes provide thread-safe timing operations, time arithmetic, and convenient system time manipulation.

The implementation lives in:

* `Utils/include/time/Timer.h` / `Utils/src/time/Timer.cpp`
* `Utils/include/time/TimeUtils.h` / `Utils/src/time/TimeUtils.cpp`

---

## 🔹 Overview

### Timer ⏲️

`r_utils::time::Timer` is a flexible, **thread-safe** timer for measuring time intervals or implementing timeouts.

* Header: `#include "time/Timer.h"`
* Namespace: `r_utils::time`
* Features:

  * Measure elapsed time in milliseconds, seconds, minutes, hours, or days
  * Supports synchronous and asynchronous start
  * Auto-stop after a duration
  * Callback on timeout
  * Thread-safe with `std::jthread` and mutex protection

---

### TimeUtils 🕰️

`r_utils::time::TimeUtils` is a static utility class to work with system time:

* Header: `#include "time/TimeUtils.h"`
* Namespace: `r_utils::time`
* Features:

  * Get current system time (`now()`)
  * Convert to/from string (`toString`, `fromString`)
  * Format time in ISO, short, date-only, or time-only formats
  * Time arithmetic: add/subtract seconds, minutes, hours, days
  * Compute differences between time points
  * Utility functions: leap year check, day of the week

---

## ⏲️ Timer — Usage Examples

### 1) Basic usage

```cpp
#include "time/Timer.h"
#include <iostream>

int main() {
    r_utils::time::Timer timer;
    timer.start();

    // simulate work
    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    timer.stop();
    std::cout << "Elapsed: " << timer.elapsedMilliseconds() << " ms\n";
}
```

---

### 2) Asynchronous timer

```cpp
#include "time/Timer.h"
#include <iostream>

int main() {
    r_utils::time::Timer timer;

    timer.startInThread(1000); // auto-stop after 1000 ms

    std::cout << "Timer started in thread..." << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));

    std::cout << "Elapsed: " << timer.elapsedMilliseconds() << " ms\n";
}
```

---

### 3) Timer with callback 🎯

```cpp
#include "time/Timer.h"
#include <iostream>

int main() {
    r_utils::time::Timer timer;

    timer.startInThread([]() {
        std::cout << "Timer callback triggered!" << std::endl;
    }, 2000); // callback after 2000 ms

    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
}
```

```cpp
#include "time/Timer.h"
#include <iostream>

int main() {
    r_utils::time::Timer timer;

    timer.startPeriodic([]() {
        std::cout << "Timer callback triggered!" << std::endl;
    }, 2000); // callback every 2000 ms

    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
}
```

---

## 🕰️ TimeUtils — Usage Examples

### 1) Get current time as string

```cpp
#include "time/TimeUtils.h"
#include <iostream>

int main() {
    std::cout << "Current time: " << r_utils::time::TimeUtils::nowString() << std::endl;
    std::cout << "Short date: " << r_utils::time::TimeUtils::nowString(r_utils::time::SHORT_DATE) << std::endl;
}
```

---

### 2) Convert string to `time_point` and back

```cpp
#include "time/TimeUtils.h"
#include <iostream>

int main() {
    auto tp = r_utils::time::TimeUtils::fromString("2025-10-24 12:00:00");
    std::cout << "TimePoint to string: " << r_utils::time::TimeUtils::toString(tp) << std::endl;
}
```

---

### 3) Time arithmetic ➕

```cpp
#include "time/TimeUtils.h"
#include <iostream>

int main() {
    auto now = r_utils::time::TimeUtils::now();
    auto later = r_utils::time::TimeUtils::addHours(now, 5);

    std::cout << "Now: " << r_utils::time::TimeUtils::toString(now) << std::endl;
    std::cout << "5 hours later: " << r_utils::time::TimeUtils::toString(later) << std::endl;
}
```

---

### 4) Differences & utility functions 🔧

```cpp
#include "time/TimeUtils.h"
#include <iostream>

int main() {
    auto t1 = r_utils::time::TimeUtils::now();
    auto t2 = r_utils::time::TimeUtils::addMinutes(t1, 120);

    std::cout << "Minutes difference: "
              << r_utils::time::TimeUtils::diffMinutes(t2, t1) << std::endl;
    std::cout << "Is 2024 a leap year? "
              << r_utils::time::TimeUtils::isLeapYear(2024) << std::endl;
    std::cout << "Day of week: "
              << r_utils::time::TimeUtils::dayOfWeek(t1) << std::endl;
}
```

---

## ⚠️ Notes & Best Practices

* **Thread safety:** `Timer` is thread-safe; `TimeUtils` is static and safe for concurrent calls.
* **Precision:** `Timer` uses `std::chrono::steady_clock` to avoid system clock changes.
* **Large durations:** `Timer` supports arbitrary durations; callbacks execute in separate threads.
* **Formatting:** Use `TimeFormat` enum for common date/time styles or provide custom `strftime` format.

---

## 🔎 Where to look next

* Implementation: `Utils/include/time/Timer.h` / `Utils/src/time/Timer.cpp`
* Implementation: `Utils/include/time/TimeUtils.h` / `Utils/src/time/TimeUtils.cpp`
* Examples: see `tests/` folder for end-to-end demonstrations.

---
