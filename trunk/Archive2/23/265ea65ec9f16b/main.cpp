#include <unordered_map>
#include <type_traits>
#include <shared_mutex>
#include <iostream>

template<class T>
struct synchronized {
  template<class F>
  std::result_of_t< F(T const&) > read( F&& f ) const {
    auto&& lock = read_lock();
    return std::forward<F>(f)(t);
  }
  template<class F>
  std::result_of_t< F(T&) > write( F&& f ) {
    auto&& lock = write_lock();
    return std::forward<F>(f)(t);
  }
private:
  mutable std::shared_timed_mutex mutex;
  std::shared_lock<std::shared_timed_mutex> read_lock() const {
    return std::shared_lock<std::shared_timed_mutex>(mutex);
  }
  std::unique_lock<std::shared_timed_mutex> write_lock() {
    return std::unique_lock<std::shared_timed_mutex>(mutex);
  }
  T t;
};

int main() {
    synchronized< std::unordered_map<int, int> > m;
    m.write( [&](auto&&m) {
        m[1] = 2;
        m[42] = 13;
    });
    m.read( [&](auto&&m) {
    for( auto&& x:m ) {
        std::cout << x.first << "->" << x.second << "\n";
    }
    });
    bool empty = m.read( [&](auto&&m) {
        return m.empty();
    });
    std::cout << empty << "\n";
    auto copy = m.read( [&](auto&&m) {
        return m;
    });
    std::cout << copy.empty() << "\n";
}