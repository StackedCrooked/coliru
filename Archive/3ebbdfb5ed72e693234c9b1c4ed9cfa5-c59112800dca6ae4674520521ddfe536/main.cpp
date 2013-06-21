#include <iostream>

#include <type_traits>
 
struct A {};
 
struct B
{
  template <typename T,
        typename = typename std::enable_if<std::is_base_of<A, T>::value, A> ::type>
  explicit B(T&)
  {
      std::cout << "templated ctor" << std::endl;
  }
  
  B(B const&)
  {
      std::cout << "copy-ctor" << std::endl;
  }
};
 
struct Foo : A, B
{
  Foo() : A(), B(*this) { }
};
 
 
int main()
{
    Foo f;
}
