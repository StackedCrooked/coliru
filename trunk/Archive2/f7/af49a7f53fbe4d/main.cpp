#include <iostream>
#include <type_traits>

template<class Expr, class T = void>
struct enable_if_valid
{
    using type = T;
};

template<class T, class U = void>
using enable_if_valid_t = typename enable_if_valid<T, U>::type;
    
void Serialize(float&)
{
}

template<typename T, typename = void>
struct has_external_serialize : std::false_type
{
};

template<typename T>
struct has_external_serialize<T, enable_if_valid_t<decltype(Serialize(std::declval<T&>()))>> : std::true_type
{
};

void Serialize(int&)
{
}

int main(int argc, const char * argv[])
{
    std::cout<<has_external_serialize<float>::value<<has_external_serialize<int>::value;
}