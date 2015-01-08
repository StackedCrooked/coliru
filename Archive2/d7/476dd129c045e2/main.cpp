#include <iostream>
#include <algorithm>
#include <functional>

template<typename T, typename U>
struct append_type;

template<typename... Ts, typename U>
struct append_type<std::tuple<Ts...>, U>
{
    using type = std::tuple<Ts..., U>;
};

template<typename>
struct function_from_tuple;

template<typename... Ts>
struct function_from_tuple<std::tuple<Ts...>>
{
    using type = std::function<bool(Ts...)>;
};

template<int N, typename T>
struct repeat
{
    using base_type = typename repeat<N - 1, T>::type;
    
    using type = typename append_type<base_type, T>::type; 
};

template<typename T>
struct repeat<0, T>
{
    using type = std::tuple<>;
};

template<int N>
struct make_function_signature
{
    using tuple_type = typename repeat<N, double>::type;
    
    using type = typename function_from_tuple<tuple_type>::type;
};

struct Position
{
    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};

template<typename T>
Position const& position_from_arg(T const& arg)
{
    return static_cast<Position const&>(arg);
}

template<typename... Ts>
bool all_of(typename make_function_signature<sizeof...(Ts)>::type predicate, Ts const&... args)
{    
    auto x_true = predicate((position_from_arg(args).x)...);
    auto y_true = predicate((position_from_arg(args).y)...);
    auto z_true = predicate((position_from_arg(args).z)...);
    
    return (x_true && y_true && z_true);
}

void foo(make_function_signature<3>::type);

int main()
{
    auto p1 = Position{0.0, 1.0, 2.0};
    auto p2 = Position{2.0, 1.0, 0.0};
    auto p3 = Position{3.0, 3.0, 3.0};
    
    auto pred2 = [&] (double p1, double p2)
    {
        return (p1 < p2);
    };

    auto pred3 = [&] (double p1, double p2, double p3)
    {
        return (p1 < (p2 + p3));
    };
    
    std::cout << all_of(pred2, p1, p2) << std::endl;
    
    std::cout << all_of(pred3, p1, p2, p3) << std::endl;
}