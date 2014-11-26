#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include <map>
#include <functional>

template <typename T>
struct ObRef{
    T t;    
};

struct A {
    std::string name;
};

struct B : public A {
    int a;    
};

template <typename T, typename _ = void>
struct picker {};

template <typename T>
struct picker<T, typename std::enable_if<std::is_base_of<A, T>::value>::type> {
  using type = ObRef<T*>;  
};

template <typename T>
struct picker<T, typename std::enable_if<!std::is_base_of<A, T>::value>::type> {
  using type = T;    
};


template <typename T>
using Trove = std::vector<typename picker<T>::type>;


int main()
{
    Trove<B> some_b;
    Trove<int> some_ints;
    ObRef<B*> b{new B};
    b.t -> a = 5;
    some_b.push_back(b);
    std::cout << some_b[0].t->a << std::endl;
}
