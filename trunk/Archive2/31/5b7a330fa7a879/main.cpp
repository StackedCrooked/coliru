#include <iostream>
#include <memory>
#include <mutex>
#include <thread>
#include <vector>

template <typename BasicLockable>
class unlock_deleter {
    std::unique_lock<BasicLockable> lock_;
public:
    unlock_deleter(BasicLockable& mtx) : lock_{mtx} {}
    unlock_deleter(BasicLockable& mtx, std::adopt_lock_t a) noexcept : lock_{mtx, a} {}
    
    template <typename T>
    void operator () (T*) const noexcept {
        // no-op
    }
};

template <typename T, typename M = std::mutex>
using locked_ptr = std::unique_ptr<T, unlock_deleter<M>>;

template <typename T, typename M = std::mutex>
class synchronized {
  T item_;
  mutable M mtx_;

  // Implement Copy/Move construction
  template <typename Other, typename N>
  synchronized(Other&& other, const std::lock_guard<N>&) :
    item_{std::forward<Other>(other).item_} {}

  // Implement Copy/Move assignment
  template <typename Other>
  synchronized& assign(Other&& other) {
    if (&other != this) {
      std::lock(mtx_, other.mtx_);
      std::lock_guard<M> _{mtx_, std::adopt_lock}, _o{other.mtx_, std::adopt_lock};
      item_ = std::forward<Other>(other).item_;
    }
    return *this;
  }

public:
  synchronized() = default;

  synchronized(const synchronized& other) :
    synchronized(other, std::lock_guard<M>(other.mtx_)) {}
  synchronized(synchronized&& other) :
    synchronized(std::move(other), std::lock_guard<M>(other.mtx_)) {}    

  template <typename N>
  synchronized(const synchronized<T, N>& other) :
    synchronized(other, std::lock_guard<N>(other.mtx_)) {}
  template <typename N>
  synchronized(synchronized<T, N>&& other) :
    synchronized(std::move(other), std::lock_guard<N>(other.mtx_)) {}    

  synchronized& operator = (const synchronized& other) & {
    return assign(other);
  }
  synchronized& operator = (synchronized&& other) & {
    return assign(std::move(other));
  }
  
  template <typename N>
  void swap(synchronized<T, N>& other) {
    if (static_cast<void*>(&other) != static_cast<void*>(this)) {
      std::lock(mtx_, other.mtx_);
      std::lock_guard<M> _{mtx_, std::adopt_lock};
      std::lock_guard<N> _o{other.mtx_, std::adopt_lock};

      using std::swap;
      swap(item_, other.item_);
    }
  }

  locked_ptr<T, M> data() & {
    return locked_ptr<T, M>{&item_, mtx_};
  }
  locked_ptr<const T, M> data() const& {
    return locked_ptr<const T, M>{&item_, mtx_};
  }
};

template <typename T, typename M, typename N>
void swap(synchronized<T, M>& a, synchronized<T, N>& b) {
  a.swap(b);
}

synchronized<std::vector<int>> foo;

void worker(int worker, int iterations, int dt) {
    for(int i=0; i<iterations; i++) {
        std::this_thread::sleep_for(std::chrono::milliseconds(dt));
        auto res = foo.data();
        // we now have a unique_lock until the end of the scope
        std::cout << "Worker " << worker << " adding " << i << std::endl;
        res->push_back(i);
    }
}

int main() {
    std::thread t1{worker, 1, 10, 173};
    std::thread t2{worker, 2, 20, 87};    
    t1.join();
    t2.join();
}
