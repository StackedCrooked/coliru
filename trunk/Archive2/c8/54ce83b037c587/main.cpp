#include <algorithm>
#include <atomic>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <memory>
#include <numeric>
#include <stdio.h>
#include <utility>
#include <vector>
#include <boost/container/vector.hpp>
#include <boost/iterator/iterator_facade.hpp>

/*
using T = unsigned;  // but can be any POD
FILE* fp = fopen( outfile.c_str(), "r" );
T* x = new T[big_n];
fread( x, sizeof(T), big_n, fp );
delete[] x;
fclose( fp );
*/

namespace cmc {
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

// Allocator adaptor that interposes construct() calls to
// convert value initialization into default initialization.
template <typename T, typename A=std::allocator<T> >
class default_init_allocator : public A {
  typedef std::allocator_traits<A> a_t;
public:
  template <typename U> struct rebind {
    using other =
      default_init_allocator<
        U, typename a_t::template rebind_alloc<U>
      >;
  };

  default_init_allocator() = default;
  using A::A;

  template <typename U>
  void construct(U* ptr) {
    ::new (static_cast<void*>(ptr)) U;
  }
  template <typename U, typename...Args>
  void construct(U* ptr, Args&&... args) {
    a_t::construct(static_cast<A&>(*this),
                   ptr, std::forward<Args>(args)...);
  }
};
} // namespace cmc

template <typename T>
class fread_iterator :
  public boost::iterator_facade<fread_iterator<T>, T,
                                std::input_iterator_tag, T> {
  friend boost::iterator_core_access;

  bool equal(const fread_iterator& other) const {
    return (file_ && feof(file_)) || n_ <= other.n_;
  }

  T dereference() const {
    // This should probably be is_trivially_copyable, but libstdc++
    // (for whatever reason) doesn't have that trait.
    static_assert(std::is_pod<T>::value, "Jabberwocky is killing user.");
    T result;
    fread(&result, sizeof(result), 1, file_);
    return result;
  }

  void increment() { --n_; }

  FILE* file_;
  std::size_t n_;

public:
  fread_iterator() : file_(nullptr), n_(0) {}
  fread_iterator(FILE* file, std::size_t n) : file_(file), n_(n) {}
};

struct FILE_deleter {
  void operator () (FILE* f) const {
    if (f) fclose(f);
  }
};
using FILE_ptr = std::unique_ptr<FILE, FILE_deleter>;

using T = uint32_t;  // but can be any POD
const auto big_n = std::size_t{64};

std::vector<T> read_file_data_iterator(const char* filename) {
  auto x = std::vector<T>{};
  if (auto fp = FILE_ptr{fopen(filename, "rb")}) {
    x.reserve(big_n);
    x.assign(fread_iterator<T>{fp.get(), big_n}, fread_iterator<T>{});
  }
  return x;
}

std::vector<T, cmc::default_init_allocator<T>>
read_file_data_allocator(const char* filename) {
  auto x = std::vector<T, cmc::default_init_allocator<T>>{};
  if (auto fp = FILE_ptr{fopen(filename, "rb")}) {
    x.resize(big_n);
    fread(x.data(), sizeof(T), big_n, fp.get());
  }
  return x;
}

boost::container::vector<T>
read_file_data_boost(const char* filename) {
  auto x = boost::container::vector<T>{};
  if (auto fp = FILE_ptr{fopen(filename, "rb")}) {
    x.resize(big_n, boost::container::default_init);
    fread(x.data(), sizeof(T), big_n, fp.get());
  }
  return x;
}

// Unused.
template <typename Range>
void dump(const Range& data) {
  std::cout << std::hex << std::setfill('0') << "Read: {\n";
  auto i = decltype(data.size()){0};
  while (i < data.size()) {
    auto j = 0;
    for (; j < 8 && i + j < data.size(); ++j) {
      std::cout << ((j != 0) ? ", " : "  ")
                << std::setw(8) << data[i + j];
    }
    if ((i += j) < data.size())
      std::cout << ',';
    std::cout << '\n';
  }
  std::cout << "};\n";
}

template <typename Function>
void time_one(const char* name, Function f) {
  const auto iterations = 100000ULL;
  f(); // pre-warm the cache
  auto t = cmc::timer{};
  auto sum = T{0};
  for (auto i = iterations; i > 0; --i) {
    auto data = f();
    sum = std::accumulate(begin(data), end(data), sum);
  }
  auto elapsed = t.elapsed<std::chrono::nanoseconds>();
  std::cout << name << ": sum = " << sum << ", " << elapsed / 1000000 << " ms ("
            << (elapsed + 0.0) / iterations / big_n << " ns per item)\n";
}

int main() {
  static const char* filename = "a.out";
  time_one("iterator", []{return read_file_data_iterator(filename);});
  time_one("allocator", []{return read_file_data_allocator(filename);});
  time_one("boost", []{return read_file_data_boost(filename);});
}
