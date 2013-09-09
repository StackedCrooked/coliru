#include <iostream>

template<typename T>
void sink(const T&x)
{
  (void)x;
}

size_t a = 0;
size_t b = 0;
size_t c = 0;

class Blah
{
public:
  Blah()
  {
    ++a;
  }
  Blah(const Blah&)
  {
    ++b;
  }
  Blah(Blah&&)
  {
    ++c;
  }
};

template<typename T>
T test1(T&&x)
{
  return std::move(x);
}

template<typename T>
T&& test2(T&&x)
{
  return std::move(x);
}

int main()
{
    Blah x;
    sink(test2(std::move(x))); // change this
  
    std::cout << "default constructor=" << a << std::endl
              << "copy constructor=" << b << std::endl
              << "move constructor=" << c << std::endl;
}

