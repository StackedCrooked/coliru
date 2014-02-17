#include <condition_variable>
#include <list>
#include <mutex>

class FairMutex {
private:
  class waitnode {
    std::condition_variable cv_;
    waitnode* next_ = nullptr;
    FairMutex& fmtx_;
  public:
    waitnode(FairMutex& fmtx) : fmtx_(fmtx) {
      *fmtx.tail_ = this;
      fmtx.tail_ = &next_;
    }

    ~waitnode() {
      for (waitnode** p = &fmtx_.waiters_; *p; p = &(*p)->next_) {
        if (*p == this) {
          *p = next_;
          if (!next_) {
            fmtx_.tail_ = &fmtx_.waiters_;
          }
          break;
        }
      }
    }

    void wait(std::unique_lock<std::mutex>& lk) {
      while (fmtx_.held_ || fmtx_.waiters_ != this) {
        cv_.wait(lk);
      }
    }

    void notify() {
      cv_.notify_one();
    }
  };

  waitnode* waiters_ = nullptr;
  waitnode** tail_ = &waiters_;
  std::mutex mtx_;
  bool held_ = false;

public:
  void lock() {
    auto lk = std::unique_lock<std::mutex>{mtx_};
    if (held_ || waiters_) {
      waitnode{*this}.wait(lk);
    }
    held_ = true;
  }

  bool try_lock() {
    if (mtx_.try_lock()) {
      std::lock_guard<std::mutex> lk(mtx_, std::adopt_lock);
      if (!held_ && !waiters_) {
        held_ = true;
        return true;
      }
    }
    return false;
  }

  void unlock() {
    std::lock_guard<std::mutex> lk(mtx_);
    held_ = false;
    if (waiters_ != nullptr) {
      waiters_->notify();
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
