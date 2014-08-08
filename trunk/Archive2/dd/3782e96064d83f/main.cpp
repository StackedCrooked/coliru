#include <string>
#include <iostream>
#include <sstream>

void print(const std::string& s)
{
  std::cout << s << std::endl;
}

template<typename T>
void identify() { std::cout << __PRETTY_FUNCTION__ << std::endl; }

template<typename T>
void identify(T&&) { identify<T>(); }

int main()
{
  int v = 1;
  identify(std::ostringstream() << "value: " << v);
}
