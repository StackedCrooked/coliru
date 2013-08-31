#include <string>
#include <iostream>

template <typename T>
class Foo
{
    public:
        typedef T type_t;
};

template <typename T>
class FooDerived : public Foo<T>
{
};

template <typename T>
class Bar : public T
{
    public:
        std::string name();
};


template<>
std::string Bar<int>::name() {
  return std::string("int");
  }

template<>
std::string Bar<float>::name() {
  return std::string("float");
  }

int main(void)
{
    Bar< FooDerived<int> > a;
    std::cout << a.name() << std::endl; // print "int" for instance
    Bar< FooDerived<float> > b;
    std::cout << b.name() << std::endl; // print "float" for instance
}