#include <array>
#include <iostream>
#include <stdexcept>
#include <string>
#include <memory>
#include <type_traits>


//
// Get index of T in Args
//
template<typename T, typename ...Args>
struct GetIndex;

template<typename T, typename ...Args>
struct GetIndex<T, T, Args...>
{
    enum { value = 0 };
};

template<typename T, typename U, typename ...Args>
struct GetIndex<T, U, Args...>
{
    enum { value = 1 + GetIndex<T, Args...>::value };
};


//
// Union helper class
//
template<typename ...Args>
struct Union;

template<typename T>
struct Union<T>
{    
    T t;    
    const T& get(std::common_type<T>) const { return t; }
    
};

template<typename T, typename ...Args>
struct Union<T, Args...>
{
    const T& get(std::common_type<T>) const { return t; }
    
    template<typename U>
    const U& get(std::common_type<U> u) const { return args.get(u); }
    
    union
    {
        T t;
        Union<Args...> args;
    };
};


//
// Variant class
//
template<typename ...Args>
struct Variant
{
    template<typename T>
    Variant(T&& t) : type_index(GetIndex<T, Args...>::value)
    {
        new (&data) T(std::forward<T>(t));
    }
    
    Union<Args...> data;
    unsigned type_index;
};

template<typename T, typename ...Args>
const T& get(const Variant<Args...>& v)
{
    return v.data.get(std::common_type<T>{});
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const Variant<T>& v)
{
    return os << get<T>(v);
}

template<typename T, typename U>
std::ostream& operator<<(std::ostream& os, const Variant<T, U>& v)
{
    if (v.type_index == 0)
    {
        return os << get<T>(v);
    }
    else
    {
        return os << get<U>(v);
    }
}

int main()
{
    std::cout << Variant<char, int>('c') << std::endl;
    std::cout << Variant<char, int>(42) << std::endl;
    
    // TODO: Fix this one
    //std::cout << Variant<char, int, std::string>(42) << std::endl;
}
