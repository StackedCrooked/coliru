#include <iostream>

namespace has {
  namespace details {
    struct _ { };
    template<typename T> struct _ make_unique (...);
  }

  namespace hack {
    using namespace details;
    using namespace std;
  }

  template<typename = void>
  class _make_unique {
    private:
      template<typename T = int>
      static constexpr bool test (decltype ((hack::make_unique<int> (T {}) = details::_ {}), 0)) { return false; }

      template<typename T = int>
      static constexpr bool test (...) { return true; }

    public:
      static constexpr bool value = test<> (0);
  };

  using make_unique = _make_unique<>;
}

int
main (int argc, char *argv[])
{
  static_assert (has::make_unique::value, "std::make_unique is not present!");
  
  std::cout << "SUCCESS";
}
