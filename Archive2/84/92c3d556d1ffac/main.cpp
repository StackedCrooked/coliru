#include <atomic>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

class Event {
  std::condition_variable cv_;
  std::mutex mtx_;
  bool signaled_ = false;

public:
  void wait() {
    std::unique_lock<std::mutex> lock{mtx_};
    while (!signaled_) {
      cv_.wait(lock);
    }
  }

  void reset() {
    std::lock_guard<std::mutex> lock{mtx_};
    signaled_ = false;
  }

  void set() {
    {
      std::lock_guard<std::mutex> lock{mtx_};
      signaled_ = true;
    }
    cv_.notify_one();
  }
};

struct MyClass {
  Event start;
  Event ready;

  unsigned long long data;
  std::atomic<bool> finished = {false};

  void processData();
  void run();
};

void MyClass::processData() {
  ++data;
}

void MyClass::run() {
  while (true) {
    start.wait();

    if (finished) {
      break;
    }

    processData();

    start.reset();
    ready.set();
  }
}

int main() {
  MyClass myc;
  std::thread processor{[&]{ myc.run(); }};
  auto data = myc.data = 0;
  myc.start.set();

  do {
    myc.ready.wait();
    myc.ready.reset();

    data = myc.data;
    myc.data *= 2;
    myc.start.set();

    std::cout << data << '\n';

  } while(data < (1ULL << 63));

  myc.finished = true;
  myc.start.set();
  processor.join();
}
