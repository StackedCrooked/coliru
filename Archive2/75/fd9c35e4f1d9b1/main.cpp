#include <iostream>
#include <type_traits>

template<class T>
struct Wrapper {};

template<class T>
struct Unwrap { using type = T; };

template<class T>
struct Unwrap<Wrapper<T> > : Unwrap<T> {};

void f(int) {
  std::cout<<"int"<<std::endl;
}

template<class T,class U=typename Unwrap<T>::type>
auto f(T) -> 
  typename std::enable_if<
    std::is_same<int,U>::value
  >::type
{
  std::cout<<"Wrapper<...<int>...>"<<std::endl;
  f(U());
}

int main() {
  f(Wrapper<int>());  
  return 0; 
}
