#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

template<typename T>
class funObj {
  std::size_t id;
  static std::size_t n;
public:
  funObj() : id(++n) 
  { 
    std::cout << "    Constructed via the default constructor, object foo with ID(" << id << ")" << std::endl;
  }
  funObj(funObj const &other) : id(++n) 
  {
    std::cout << "    Constructed via the copy constructor, object foo with ID(" << id << ")" << std::endl;
  }
  ~funObj()
  { 
    std::cout << "    Destroyed object foo with ID(" << id << ")" << std::endl;
  }
  void operator()(T &elem)
  { 
  
  }
  T operator()()
  {
    return 1;
  }
};

template<typename T>
void func(funObj<T> obj) { obj();  }

template<typename T>
std::size_t funObj<T>::n = 0;

int main()
{
  std::vector<int> v{ 1, 2, 3, 4, 5, };
  std::cout << "> Calling `func`..." << std::endl;
  func(funObj<int>());
  std::cout << "> Calling `for_each`..." << std::endl;
  std::for_each(std::begin(v), std::end(v), funObj<int>());
  std::cout << "> Calling `generate`..." << std::endl;
  std::generate(std::begin(v), std::end(v), funObj<int>());

  // std::ref 
  auto fobj1 = funObj<int>();
  std::cout << "> Calling `for_each` with `ref`..." << std::endl;
  std::for_each(std::begin(v), std::end(v), std::ref(fobj1));
  std::cout << "> Calling `generate` with `ref`..." << std::endl;
  std::for_each(std::begin(v), std::end(v), std::ref(fobj1));
  return 0;
}