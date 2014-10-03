#include <type_traits>

struct X {
  bool flag = false;
  std::aligned_storage<sizeof(int), alignof(int)>::type storage;
  
  constexpr X() {}
};

int main()
{
    constexpr X x;
}