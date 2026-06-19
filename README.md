# PointerGuard-CPP 🛡️

A lightweight, custom dynamic memory tracker built in C++ to monitor heap allocations and prevent common memory management bugs.

## Core Features

- **Leak Detection:** Intercepts and tracks heap allocations (`new` and `delete`), reporting unreleased memory at program termination.
- **Dangling Pointer Prevention:** Explicitly sets freed pointers to `nullptr` post-deletion to ensure safe memory access.
- **Double-Free Protection:** Hardened architecture with deleted copy and move constructors to prevent duplicate memory deallocation crashes.

_Built to demonstrate low-level memory management and safe object-oriented principles in C++._
