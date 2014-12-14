#include <iostream>

template<typename... ArgTypes>
void print(ArgTypes... args);
template<typename T, typename... ArgTypes>
void print(T t, ArgTypes... args)
{
  std::cout << t;
  print(args...);
}
template<> void print() {} // end recursion

int main()
{
  print("Random ", 'c', "ollection of ", 5, " arguments.\n");
}