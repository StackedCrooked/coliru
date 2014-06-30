#include <cstdint>

struct foo {
  static constexpr intptr_t ptr = 0x1;
};

    class C
    {
      public:
        static constexpr intptr_t noop = 0x1 ;
    };

auto main() -> int {
  
  void * vp1 = reinterpret_cast<void*>(foo::ptr) ;
  
  const void * vp2 = reinterpret_cast<const void*>( C::noop ) ;
  
  return 0;
}