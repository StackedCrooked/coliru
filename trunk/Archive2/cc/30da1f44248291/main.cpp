#include <type_traits>
#include <iostream>
#include </Archive2/72/86e6cd9dd639f1/main.cpp>

template<typename... Args>
size_t sum (Args... args)
{
  auto result = static_if<sizeof... (args) != 1> {} (
    [&](auto x, auto... xs) { return x + sum (xs...); },   // multi
    [&](auto x)             { return x;                },  // single
    args...
  );

  return result;
}

int
main (int argc, char *argv[])
{
    std::cout << sum (1,2,3,100);
}