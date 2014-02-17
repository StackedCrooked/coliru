// FairLock.hpp
#include <condition_variable>
#include <list>
#include <mutex>

class FairMutex {
private:
  struct waitnode {
    std::condition_variable cv;
    waitnode* next = nullptr;
  };

  waitnode* waiters = nullptr;
  waitnode** tail = &waiters;
  std::mutex mtx;
  bool held = false;

public:
  void lock() {
    auto lk = std::unique_lock<std::mutex>{mtx};
    if (held || waiters) {

      waitnode waiter;
      *tail = &waiter;
      tail = &waiter.next;

      while (held || waiters != &waiter) {
        waiter.cv.wait(lk);
      }

      waiters = waiter.next;
      if (!waiters) {
        tail = &waiters;
      }
    }
    held = true;
  }

  bool try_lock() {
    if (mtx.try_lock()) {
      std::lock_guard<std::mutex> lk(mtx, std::adopt_lock);
      if (!held && !waiters) {
        held = true;
        return true;
      }
    }
    return false;
  }

  void unlock() {
    std::lock_guard<std::mutex> lk(mtx);
    held = false;
    if (waiters != nullptr) {
      waiters->cv.notify_one();
    }
  }
};

#include <chrono>
#include <iostream>
#include <random>
#include <thread>

FairMutex fmtx;
const int n_loops = 10;
const int n_threads = 4;

void do_thread(int id) {
  auto engine = std::mt19937{std::random_device{}()};
  auto dist = std::uniform_int_distribution<>{0,250};
  auto rng = [&](){return dist(engine);};
  std::this_thread::sleep_for(std::chrono::milliseconds{rng()});

  for (auto i = n_loops; i > 0; --i) {
    {
      std::lock_guard<FairMutex> lk{fmtx};
      std::cout << "Thread " << id << " on iteration " << i << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds{rng()});
    }
    std::this_thread::sleep_for(std::chrono::milliseconds{25});
  }
}

int main() {
  auto threads = std::array<std::thread, n_threads>{{}};
  for (int i = 0; i < int(threads.size()); ++i) {
    threads[i] = std::thread(do_thread, i);
    std::this_thread::sleep_for(std::chrono::milliseconds{500});
  }
  for (auto&& t : threads) {
    t.join();
  }
}
