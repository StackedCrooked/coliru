#include <mutex>

class synchronized_int {
  mutable std::mutex mtx;
  int value;
public:
  synchronized_int(int v = 0) : value(v) {}

  // Move initialization
  synchronized_int(synchronized_int&& other) {
    std::lock_guard<std::mutex> lock(other.mtx);
    value = std::move(other.value);
    other.value = 0;
  }

  // Copy initialization
  synchronized_int(const synchronized_int& other) {
    std::lock_guard<std::mutex> lock(other.mtx);
    value = other.value;
  }

  // Move assignment
  synchronized_int& operator = (synchronized_int&& other) {
    std::lock(mtx, other.mtx);
    std::lock_guard<std::mutex> self_lock(mtx, std::adopt_lock);
    std::lock_guard<std::mutex> other_lock(other.mtx, std::adopt_lock);
    value = std::move(other.value);
    other.value = 0;
    return *this;
  }

  // Copy assignment
  synchronized_int& operator = (const synchronized_int& other) {
    std::lock(mtx, other.mtx);
    std::lock_guard<std::mutex> self_lock(mtx, std::adopt_lock);
    std::lock_guard<std::mutex> other_lock(other.mtx, std::adopt_lock);
    value = other.value;
    return *this;
  }
};

int main() {
    synchronized_int foo{42};
    synchronized_int bar = foo; // Copy init
    synchronized_int baz = std::move(foo); // Move init
    foo = baz; // Copy assignment
    bar = std::move(baz); // Move assignment
}
