#include <iostream>
#include <type_traits>
#include <vector>
#include <utility>

template<class T>
auto update_callable(const std::vector<T>&, ...) 
    -> void
{ 
}

template< class T, class... Args>
auto update_callable( const std::vector<T>& objects, Args&&... args) 
    -> decltype(std::declval<T>()(std::forward<Args>(args)...))
{ 
    for (auto&& elem : objects)
        elem(std::forward<Args>(args)...);
}

template< class T, class... Args>
auto update_callable( const std::vector<T>& objects, Args&&... args) 
    -> decltype(std::declval<T>()())
{ 
    for (auto&& elem : objects)
        elem();
}

struct N {};

struct Z 
{ 
    void operator()() const
    { std::cout << "Z(), "; }
};

struct T
{   
    void operator()(int x, int y) const
    { std::cout << "T(," << x << "," << y << "), "; }
};

int main()
{
    auto vN = std::vector<N>(1); 
    auto vZ = std::vector<Z>(2); 
    auto vT = std::vector<T>(3); 
    
    update_callable(vN, 1, 2);std::cout << "end of 1st\n";
    update_callable(vZ, 1, 2);std::cout << "end of 2nd\n";
    update_callable(vT, 1, 2);std::cout << "end of 3rd\n";
}
