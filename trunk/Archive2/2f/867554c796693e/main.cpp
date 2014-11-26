#include <iostream>
#include <string>
#include <type_traits>
#include <vector>
#include <map>
#include <functional>

template <typename T>
struct ObRef{
    ObRef(T t) : t{std::move(t)} {}
    T operator->(){
        return t;
    }
    T t;
};

struct Ankle {
    std::string name;
};

struct B : public Ankle {
    int bar;    
};

template <typename T, typename _ = void>
struct picker {};

template <typename T>
struct picker<T, typename std::enable_if<std::is_base_of<Ankle, T>::value>::type> {
  using type = ObRef<T*>;  
};

template <typename T>
struct picker<T, typename std::enable_if<!std::is_base_of<Ankle, T>::value>::type> {
  using type = T;    
};


template <typename T>
using Trove = std::vector<typename picker<T>::type>;


int main()
{
    Trove<B> some_b;
    auto b = new B;
    b -> bar = 5;
    some_b.push_back(b);
    std::cout << some_b[0]->bar << std::endl;
    Trove<int> some_ints;
    some_ints.push_back(5);
}
