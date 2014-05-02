#include <typeindex>
#include <vector>
#include <iostream>

std::vector<std::type_index> vec;

template<typename T>
void Fill() {
    vec.push_back(typeid(T));
}

template <typename T1, typename T2, typename... Tn>
void Fill() {
    Fill<T1>();
    Fill<T2, Tn...>();
}

int main()
{
    Fill<int,double>();
    std::cout << vec.size() << std::endl;    
}

