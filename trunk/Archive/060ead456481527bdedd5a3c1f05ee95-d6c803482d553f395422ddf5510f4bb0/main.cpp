#include <cassert>
#include <iostream> // std::cout
#include <thread>
#include <vector>
#include <mutex>
 
class Number;
std::ostream& operator<<(std::ostream& stream, const Number& number);
 
class Number {
 public:
  Number() : v_(1) {}
 
  // thread-safe update of 'a' and 'b'
  static void update(Number& a, Number& b, bool order) {
    // do not lock 'mutex_' of 'a' and 'b' sequentially,
    // two sequential lock may lead to deadlock,
    // that's why 'std::lock' exists (see below)
    GuardLock lock_a(a.mutex_, std::defer_lock);
    GuardLock lock_b(b.mutex_, std::defer_lock);
 
    // mutexes is not locked
    assert(!lock_a.owns_lock());
    assert(!lock_b.owns_lock());
 
    // unspecified series of calls...
    std::lock(lock_a, lock_b);
 
    // Result: 'a.mutex_' and 'b.mutex_' is in locked state
    // 'a' and 'b' can be modified safety
    assert(lock_a.owns_lock());
    assert(lock_b.owns_lock());
 
    if (order) {
      a.v_ += b.v_;
      b.v_ += a.v_;
 
      std::cout << a << b;
    }
    else {
      b.v_ += a.v_;
      a.v_ += b.v_;
 
      std::cout << b << a;
    }
 
    // 'lock_a' and 'lock_b' will be destroyed,
    // unlocking 'a.mutex_' and 'b.mutex_'
  }
 
  // not thread-safe; used before thread creation or in thread-safe 'update'
  std::ostream& print(std::ostream& stream) const {
    stream << v_ << " ";
    return stream;
  }
 
 private:
  using Mutex = std::mutex;
  using GuardLock = std::unique_lock<Mutex>;
 
  Mutex mutex_;
  int v_;
};
 
// not thread-safe; see 'Number::print'
std::ostream& operator<<(std::ostream& stream, const Number& number) {
  return number.print(stream);
}
 
int main() {
  Number a, b;
  std::cout << a << b;
 
  std::vector<std::thread> threads;
 
  for (unsigned i = 0; i < 4; ++i) {
    // without 'std::lock' deadlock may occur in this situation:
    //   thread #1 lock 'a.mutex_'
    //   thread #2 lock 'b.mutex_'
    //   thread #1 try to lock 'b.mutex_' and blocked (it's locked by #2)
    //   thread #2 try to lock 'a.mutex_' and blocked (it's locked by #1)
    //   ... deadlock
    threads.emplace_back(Number::update, std::ref(a), std::ref(b), true); // #1
    threads.emplace_back(Number::update, std::ref(b), std::ref(a), false); // #2
  }
 
  for (auto& i: threads) {
    i.join();
  }
 
  std::cout << '\n';
}