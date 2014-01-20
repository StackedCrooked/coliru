#include <memory>
#include <utility>
#include <vector>

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

std::vector<int> with_default_allocator() {
    return std::vector<int>(10);
}

std::vector<int, default_init_allocator<int>> with_custom_allocator() {
    return std::vector<int, default_init_allocator<int>>(10);
}
