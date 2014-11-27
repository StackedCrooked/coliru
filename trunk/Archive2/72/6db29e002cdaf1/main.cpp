#include <type_traits>


namespace Detail {


template<typename T>
T Min(T t)
{
    return t;
}


template<typename T>
T Min(T a, T b)
{
    return b < a ? b : a;
}


template<typename T, typename ...Tail>
T Min(T a, T b, Tail ...tail)
{
    // enable (theoretically) instruction-level parallelism
    return Min(Min(a, b), Min(tail...));
}


template<typename T>
T Max(T t)
{
    return t;
}


template<typename T>
T Max(T a, T b)
{
    return b < a ? a : b;
}


template<typename T, typename ...Tail>
T Max(T a, T b, Tail ...tail)
{
    // enable (theoretically) instruction-level parallelism
    return Max(Max(a, b), Max(tail...));
}


} // namespace Detail


template<typename ...T>
typename std::common_type<T...>::type Min(T&& ...args)
{
    typedef typename std::common_type<T...>::type CommonType;
    return Detail::Min(static_cast<CommonType>(args)...);
}


template<typename ...T>
typename std::common_type<T...>::type Max(T&& ...args)
{
    typedef typename std::common_type<T...>::type CommonType;
    return Detail::Max(static_cast<CommonType>(args)...);
}



// test
int main()
{
    return Min(Max(5, 3), Max(2, 4));
}
