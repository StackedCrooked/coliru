#include <cstddef>
#include <iostream>
#include <memory>
#include <new>
#include <type_traits>
#include <utility>

struct placement_delete {
  template <typename T>
  void operator()(T* ptr) {
    ptr->~T();
  }
};

template <typename T>
using placement_ptr = std::unique_ptr<T, placement_delete>;

class Base {
  // ...
};

template <std::size_t N, std::size_t Align = 0>
class buffer {
public:
  template <typename T, typename...Args>
  placement_ptr<T> emplace(Args&&...args) {
    static_assert(std::is_base_of<Base, T>(),
                  "Only classes derived from Base can go in a buffer.");
    static_assert(sizeof(T) <= sizeof(space_),
                  "Type is too big for buffer.");
    static_assert(alignof(decltype(space_)) % alignof(T) == 0,
                  "Buffer alignment is insufficient for type.");
    return placement_ptr<T>{::new(&space_) T(std::forward<Args>(args)...)};
  }
private:
  typename std::conditional<!Align,
    typename std::aligned_storage<N>::type,
    typename std::aligned_storage<N, Align>::type
  >::type space_;
};

class Foo : Base {
public:
  Foo() { std::cout << "construct Foo @" << this << '\n'; }
  ~Foo() { std::cout << "destroy Foo @" << this << '\n'; }
};

class TooBig : Base {
  unsigned char lots_of_bytes[1024];
};

int main() {
  constexpr std::size_t limit = 42;
  buffer<limit> buf1;
  auto fptr = buf1.emplace<Foo>();
    
#ifdef BAD_CASE
    buffer<limit> buf2;
    auto tbptr = buf2.emplace<TooBig>(); // static_assert fails.
#endif
}
