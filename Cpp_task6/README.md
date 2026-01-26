# C++ Multi-threaded Capslock Monitor:

- A simple C++ multithreaded application that monitors the Caps Lock key state on Linux and logs (to console and file) when it's activated.


## Build & Run
```bash
g++ -std=c++14 -pthread -o capslock_monitor threads_task.cpp
./threads_task
```