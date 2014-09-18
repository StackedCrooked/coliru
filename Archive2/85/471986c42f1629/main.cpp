#include <iostream>
#include <type_traits>


    template<typename... Ts>
    struct make_void { typedef void type;};
    
    template<typename... Ts>
    using void_t = typename make_void<Ts...>::type;

void Serialize(float&)
{
}

template<typename T, typename = void>
struct has_external_serialize : std::false_type
{
};

template<typename T>
struct has_external_serialize<T, void_t<decltype(Serialize(std::declval<T&>()))>> : std::true_type
{
};

void Serialize(int&)
{
}

int main()
{
    std::cout<<has_external_serialize<float>::value<<has_external_serialize<int>::value << std::endl;
}