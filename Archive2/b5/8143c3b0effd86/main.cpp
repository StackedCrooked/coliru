#include <array>
#include <atomic>
#include <cassert>
#include <thread>

class spinning_barrier {
public:
    spinning_barrier(unsigned int n) : n_threads_(n), counter_(n) {
        assert(!(n & step_mask));
    }

    void wait();

private:
    /* Number of synchronized threads. */
    const unsigned int n_threads_;

    /* Number of threads currently spinning.  */
    static const unsigned int step_mask = ~(~0u >> 1);
    std::atomic<unsigned int> counter_;
};

void spinning_barrier::wait() {
    auto const old = counter_.fetch_add(-1, std::memory_order_relaxed);
    auto const step = old & step_mask;
    auto const count = old & ~step_mask;

    if (count == 1) {
        /* OK, last thread to come.  */
        counter_.store((step ^ step_mask) | n_threads_, std::memory_order_release);
    } else {
        /* Run in circles and scream like a little girl.  */
        while ((counter_.load(std::memory_order_acquire) & step_mask) == step)
            ;
    }
}

int main() {
  static const std::size_t n_iterations = 20000000;
  static const std::size_t n_threads = 2;
  spinning_barrier barrier{n_threads};
  auto spin = [&barrier]{
    for(std::size_t count = 0; count < n_iterations; ++count)
      barrier.wait();
    };
  std::array<std::thread,n_threads - 1> threads;
  for (auto&& t : threads) {
    t = std::thread{spin};
  }
  spin();
  for (auto&& t : threads) {
    t.join();
  }
}
