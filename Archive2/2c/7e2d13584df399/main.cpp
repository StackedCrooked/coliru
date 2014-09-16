#include <iostream>
#include <stdexcept>
#include <cstdlib>

namespace N { class C; }
void *operator new(size_t, N::C&);
void operator delete(void *, N::C&);
  
namespace N {

class C {
  void fn(bool b)
  {
    std::cout << b << std::endl;
  }

  friend void *::operator new(size_t, C&);
  friend void ::operator delete(void *, C&);

  public:
  C(bool b)
  {
    if (b) {
      throw std::runtime_error("");
    }
  }
};

}

void *operator new(std::size_t size, N::C& storage)
{
  storage.fn(true);
  return std::malloc(size);
}

void operator delete(void *pointer, N::C& storage)
{
  storage.fn(false);
  std::free(pointer);
}

int main()
{
  try {
    N::C c(false);
    new (c) bool(true);
  }
  catch (...) {
  }
}