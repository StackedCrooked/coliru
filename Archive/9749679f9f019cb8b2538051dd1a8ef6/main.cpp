#include <iostream>

inline void dummy(...) {}

template <typename T>
int repeater(int &n, const T& val)
{
    std::cout << '.';
    ++n;
    // Silence compiler warnings about unused val:
    (void)val;
    return 0;
}

template <typename... Args>
void TestVariadic(const Args&... args)
{
    int n = 0;
    dummy(repeater(n, args)...);

    std::cout << "\nValue of n:" << n << std::endl;
}

int main ()
{
  int p = 5;
  TestVariadic(4, 'a', p, "string");

  return 0;
}