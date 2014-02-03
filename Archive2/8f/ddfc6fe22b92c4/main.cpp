#include <atomic>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <numeric>
#include <vector>

namespace {
class timer {
    using hrc = std::chrono::high_resolution_clock;
    hrc::time_point start;

    static hrc::time_point now() {
      // Prevent memory operations from reordering across the
      // time measurement. This is likely overkill, needs more
      // research to determine the correct fencing.
      std::atomic_thread_fence(std::memory_order_seq_cst);
      auto t = hrc::now();
      std::atomic_thread_fence(std::memory_order_seq_cst);
      return t;
    }

public:
    timer() : start(now()) {}

    hrc::duration elapsed() const {
      return now() - start;
    }

    template <typename Duration>
    typename Duration::rep elapsed() const {
      return std::chrono::duration_cast<Duration>(elapsed()).count();
    }

    template <typename Rep, typename Period>
    Rep elapsed() const {
      return elapsed<std::chrono::duration<Rep,Period>>();
    }
};

const std::vector<int>& f() {
    static const auto x = std::vector<int>{ 1, 2, 3 };
    return x;
}

static const auto y = std::vector<int>{ 1, 2, 3 };
const std::vector<int>& g() {
    return y;
}

const unsigned long long n_iterations = 500000000;

template <typename F>
void test_one(const char* name, F f) {
  f(); // First call otusidse the timer.

  using value_type = typename std::decay<decltype(f()[0])>::type;
  std::cout << name << ": " << std::flush;

  auto t = timer{};
  auto sum = uint64_t{};
  for (auto i = n_iterations; i > 0; --i) {
    const auto& vec = f();
    sum += std::accumulate(begin(vec), end(vec), value_type{});
  }
  const auto elapsed = t.elapsed<std::chrono::milliseconds>();
  std::cout << elapsed << " ms (" << sum << ")\n";
}
} // anonymous namespace

int main() {
  test_one("local static", f);
  test_one("global static", g);
}
