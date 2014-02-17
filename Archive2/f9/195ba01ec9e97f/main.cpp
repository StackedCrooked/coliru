#include <iostream>
#include <atomic>

struct S { S() noexcept { std::cout << "s\n"; }};

int main()
{
  std::cout << __VERSION__ << '\n';
  std::atomic<S> s;
  //std::atomic_init(&s, S());
}
