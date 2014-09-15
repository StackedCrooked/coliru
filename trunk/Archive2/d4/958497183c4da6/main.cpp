#include <type_traits>
#include <iostream>

template<class From, class To, class Value>
struct convert
{
    template <typename F = From, typename T = To>
    static auto apply(Value value) -> typename std::enable_if<std::is_same<F,T>::value, Value>::type
    {
        static_assert(std::is_same<F, From>::value && std::is_same<T, To>::value, "");
        std::cout << "Same" << std::endl;
        return value;
    }
    
    template <typename F = From, typename T = To>
    static auto apply(Value value) -> typename std::enable_if<!std::is_same<F,T>::value, Value>::type
    {
        static_assert(std::is_same<F, From>::value && std::is_same<T, To>::value, "");
        std::cout << "Not the same" << std::endl;
        return value;
    }
};


int main()
{
    convert<int, int, float>::apply(3.14f);
    convert<int, float, float>::apply(3.14f);
    
    //convert<int, int, float>::apply<int,float>(3.14f); you can't hack!
}
