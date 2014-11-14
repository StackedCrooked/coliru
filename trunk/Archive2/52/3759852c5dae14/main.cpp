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
    
    
template<typename ...T> void eval(T&&...)
{
}


template<typename T>
std::ostream& print(std::ostream& os, T t)
{
    return os << t;
}


template<typename ...T>
struct Tuple
{
    // this is a list of member variables
    using Storage = decltype(make_storage(std::declval<T>()...));
    Storage unpack_into;

    template<typename ...U>
    Tuple(U&& ...u) : unpack_into(make_storage(std::forward<U>(u)...)) // initialize our member variables
    {
    }
    
    Tuple(Tuple&) = default;  // hack
    Tuple(Tuple&&) = default;
    
    
    friend std::ostream& operator<<(std::ostream& os, const Tuple& tup)
    {
        tup.unpack_into([&](auto ...x) {
            eval(print(os, x)...);
        });
        return os;
    }
};


template<typename ...T>
auto make_tuple(T ...t)
{
    return Tuple<T...>(std::forward<T>(t)...);
}


template<typename Xs, typename Ys>
auto tuple_cat(Xs xs, Ys ys)
{
    return xs.unpack_into([=](auto ...x) {
        return ys.unpack_into([=](auto ...y) {
            return make_tuple(x..., y...);
        });
    });
}


int main()
{
    Tuple<int, int, int> t1 = make_tuple(1, 2, 3);
    Tuple<int, int, int> t2 = make_tuple(4, 5, 6);
    
    std::cout << t1 << std::endl;
    std::cout << t2 << std::endl;
    std::cout << tuple_cat(t1, t2) << std::endl;
    std::cout << tuple_cat(tuple_cat(t1, t2), tuple_cat(t1, t2)) << std::endl;
}


