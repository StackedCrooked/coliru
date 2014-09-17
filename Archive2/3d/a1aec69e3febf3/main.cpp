#include <iostream>
#include <type_traits>

template<class...>
struct voider {
  using type = void;
};
template<typename...Args>
using void_t = typename voider<Args...>::type;

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