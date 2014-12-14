#include <iostream>

struct expand_type {
  template<typename... T>
  expand_type(T&&...) {}
};
template<typename... ArgTypes>
void print(ArgTypes... args)
{ 
  expand_type{ 0, (std::cout << args, 0)... };
}

int main()
{
  print("Random ", 'c', "ollection of ", 5, " arguments.\n");
}