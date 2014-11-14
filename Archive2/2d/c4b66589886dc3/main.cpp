#include <iostream>
#include <cstring>



template<typename ...T>
decltype(auto) make_storage(T ...t)
{
    return [t...](auto&& f) -> decltype(auto)
    {
        return std::forward<decltype(f)>(f)(t...);
    };
}


template<typename ...T>
struct Tuple
{
    // this is a list of member variables
    decltype(make_storage(std::declval<T>()...)) storage;

    template<typename ...U>
    Tuple(U&& ...u) : storage(make_storage(std::forward<U>(u)...)) // initialize our member variables
    {
    }
};


template<typename ...T>
auto make_tuple(T ...t)
{
    return Tuple<T...>(std::forward<T>(t)...);
}


int main()
{
    auto tuple = make_tuple(1, short(2), '3', false); // returns a Tuple<int, short, char, bool>

    // verification
    
    // make a struct with identical layout
    struct Fields { int i; short s; char c; bool b; };
    
    // check size and alignment
    static_assert(sizeof(Fields) == sizeof(tuple), "");
    static_assert(alignof(Fields) == alignof(tuple), "");

    // check contents
    Fields fields{};
    std::memcpy(&fields, &tuple, sizeof(tuple));
    std::cout << std::boolalpha
              << fields.i << ' '
              << fields.s << ' '
              << fields.c << ' '
              << fields.b << '\n';
}
