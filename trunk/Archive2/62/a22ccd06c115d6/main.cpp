#include <type_traits>

template <typename T>
using alias = T;

template <bool B>
struct Bool : std::integral_constant<bool, B> {};

typedef Bool<true> True;
typedef Bool<false> False;

template <typename T>
struct enable_if_t : std::enable_if<T::value, int> {};
template <typename T>
struct disable_if_t : std::enable_if<!T::value, int> {};

template <typename T>
using Invoke = typename T::type;

template <typename T>
using EnableIf = Invoke<enable_if_t<T>>;

template <typename T>
using DisableIf = Invoke<disable_if_t<T>>;

template <typename Condition, typename Then, typename Else>
using If = Invoke<std::conditional<Condition::value, Then, Else>>;

template <typename... T>
struct any : False {};
template <typename H, typename... T>
struct any<H, T...> : If<H, True, any<T...>>{};
template <typename... T>
using Any = Invoke<any<T...>>;

template <typename... T>
struct all : True {};
template <typename H, typename... T>
struct all<H, T...> : If<H, all<T...>, False>{};
template <typename... T>
using All = Invoke<all<T...>>;



#include <array>
#include <algorithm>



namespace detail
{
    template<typename T, size_t N>
    struct storage
    {
        std::array<T, N> data;
        
        storage() : data({0}) {}

        storage(const std::array<T,N>& init) : data(init) {}
        
        template <typename... U,
                  EnableIf<All<std::is_same<T,U>...>> = 0,
                  EnableIf<Bool<sizeof...(U) == N>> = 0>
        storage(U&&... values) : data({values...}) {}
    };
    
    template<typename T>
    struct storage<T,3>
    {
        union
        {
            std::array<T, 3> data;
            struct { T x, y, z; };
            struct { T u, v, w; };
            struct { T r, g, b; };
        };
        
        storage() : data({0}) {}
        
        storage(const std::array<T, 3>& init) : data(init) {}
        
        storage(T a, T b, T c) : data({a,b,c}) {}
    };
}

template <typename T, size_t N>
struct thing : public detail::storage<T, N>
{
    using detail::storage<T,N>::storage;
    
    thing(T value = 0) : detail::storage<T,N>({value}) {}
    
    T length() const { T sum = 0; for(const auto& e : detail::storage<T,N>::data) sum += e*e; return std::sqrt(sum); }
    
    //other functions, operators and stuff here, only once
};
    
    

#include <iostream>
int main()
{
    thing<int,3> t1(1,2,3);
    std::cout << t1.length() << "\n";
    
    thing<float,3> t2(1.0f, 1.0f, 0.0f);
    std::cout << t2.length() << "\n";
    
    thing<double, 5> t3(7);
    std::cout << t3.length() << "\n";
}