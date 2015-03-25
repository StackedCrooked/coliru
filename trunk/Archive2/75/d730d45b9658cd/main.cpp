// transform algorithm example
#include <iostream>     // std::cout
#include <memory>
#include <vector>
#include <type_traits>


template <typename T>
auto move_if_cannot_copy(T& x) -> std::enable_if_t<std::is_copy_constructible<T>::value, T&>
{
    return x;
}

template <typename T>
auto move_if_cannot_copy(T& x) -> std::enable_if_t<!std::is_copy_constructible<T>::value, T&&>
{
    return std::move(x);
}

class OnlyMovable {
public:
    OnlyMovable(){}
    OnlyMovable(OnlyMovable const&) = delete;
    OnlyMovable(OnlyMovable &&){}
};

class Copiable {
public:
    Copiable(){}
};

int main () {
    
     Copiable c;
     Copiable c2{move_if_cannot_copy(c)};

     OnlyMovable m;
     OnlyMovable m2{move_if_cannot_copy(m)};   
  
    return 0;
}
