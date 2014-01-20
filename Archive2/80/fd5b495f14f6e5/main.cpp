#include <map>
#include <iostream>



template<typename T>
constexpr T pi = T(3.1415926535897932385);


template<typename T>
T area_of_circle_with_radius(T r) {
    return pi<T> * r * r;
}





/*template <typename T>
std::map<int, T> storage;

template<typename T>
void some_func(T value)
{ 
    auto store = [&](auto val) { storage<typename decltype(storage<T>)::value_type::second_type>.insert(val); };

    store(std::pair<int, T>(0, value));
    store(std::pair<int, T>(2, value));
}*/

int main()
{
    std::cout<<area_of_circle_with_radius(10000);
}