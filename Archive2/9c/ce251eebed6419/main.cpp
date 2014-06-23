#include <iostream>
#include <array>

template<typename T, std::size_t N>
class Base
{
private:
    std::array<T, N> const &array;
public:
    Base(std::array<T, N> const &a) : array(a) { }
    void print() const {
      std::cout << "Printing array from Base class!" << std::endl;
      for(auto i : array) std::cout << i << " ";
      std::cout << std::endl;
    }
};

template<typename T, std::size_t N>
class Child : public Base<T, N> {
private :
  std::array<T, N> array;
public:
  Child() : Base<T, N>(array) { 
    for(auto &i : array) i = 10;
  }

  void print() {
    std::cout << "Printing array from Child class!" << std::endl;
    for(auto i : array) std::cout << i << " ";
    std::cout << std::endl;
  }
};

auto main() -> int {
  Child<int, 10> c;
  c.print();
  Base<int, 10> *b = &c;
  b->print();
  
  return 0;
}
