
#include <fcntl.h>
#include <unistd.h>

#include <string>

#include <condition_variable>
#include <mutex>
#include <thread>

#include <iostream>

using namespace std::chrono_literals;

std::mutex mx;
std::condition_variable cv;

// shared variable (indicating if the capslock is on)
bool notified = false;

int main(int argc, char const *argv[]) {

// thread : read the capslock state 
  std::thread readCapsLock([&]() {
    //default value
    char prev_ch = '0';

    while (1) {
      char ch;
      int fd_caps =
          open("/sys/class/leds/input7::capslock/brightness", O_RDONLY);

      read(fd_caps, &ch, sizeof(ch));
      close(fd_caps);


      //  open a scope for the lock
      {
        std::lock_guard<std::mutex> lock(mx);
        if (ch == '1'&& ch != prev_ch) {
          notified = true;
          cv.notify_one();
        } else if (ch == '0') {
          notified = false;
        }
      }
      prev_ch = ch;
      std::this_thread::sleep_for(100ms);

    }
  });

  // thread : write on console and file if the capslock is on
  std::thread writeCapsLock([&]() {
    while (1) {
      std::unique_lock<std::mutex> lock(mx);

      cv.wait(lock, [&]() { return notified; });
      notified = false;

      int fd_log = open("./capslock.txt", O_RDWR | O_CREAT | O_APPEND, S_IRWXU);

      std::cout << "Capslock is on\n";
      write(fd_log, "Capslock is on\n", 15);

      close(fd_log);

    }
  });

  writeCapsLock.join();
  readCapsLock.join();

  return 0;
}
