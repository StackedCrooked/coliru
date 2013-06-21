#include <iostream>

#include <type_traits>
 
struct A {};
 
struct B
{
  template <typename T,
        typename = typename std::enable_if<std::is_same<typename std::decay<T>::type, A>::value>::type>
  explicit B(T)
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
