#include <typeindex>
#include <vector>
#include <iostream>

std::vector<std::type_index> vec;

template<typename T>
void Fill(){
    vec.emplace_back(typeid(T)); // pretty sure you want emplace_back here ;)
}

template<typename T1, typename ... Tn>
void Fill(){
    Fill<T1>();
    Fill<Tn...>();
}

int main()
{
    Fill<int,double>();
    std::cout << vec.size() << std::endl;    
}

