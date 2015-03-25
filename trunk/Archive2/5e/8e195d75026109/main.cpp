// transform algorithm example
#include <iostream>     // std::cout
#include <memory>
#include <vector>
#include <type_traits>


template <typename T>
std::enable_if_t<std::is_copy_constructible<T>::value, T const&>
move_if_cannot_copy(T const& x)
{
    return x;
}

template <typename T>
std::enable_if_t<!std::is_copy_constructible<T>::value, T const&&>
move_if_cannot_copy(T const& x)
{
    return std::move(x);
}

template <typename T>
std::enable_if_t<!std::is_copy_constructible<T>::value, T&&>
move_if_cannot_copy(T& x)
{
    return std::move(x);
}

class OnlyMovable {
public:
    OnlyMovable(){}
    OnlyMovable(OnlyMovable const&) = delete;
    OnlyMovable(OnlyMovable &&){std::cout << "moving OnlyMovable" << std::endl;}
    OnlyMovable(OnlyMovable const&&){std::cout << "strange moving OnlyMovable" << std::endl;}
};

class Copiable {
public:
    Copiable(){}
    Copiable(Copiable const&){std::cout << "copying Copiable" << std::endl;}
    Copiable(Copiable &&){std::cout << "moving Copiable" << std::endl;}
};

int main () {
    
    const Copiable c;
    Copiable c2{move_if_cannot_copy(c)};

    OnlyMovable m;
    OnlyMovable m2{move_if_cannot_copy(m)};   
     
    const OnlyMovable constm;
    OnlyMovable m3{move_if_cannot_copy(constm)};   
  
    return 0;
}
