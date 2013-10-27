#include <iostream>

struct A{};
struct B{};
struct C{};

struct D{};
struct E{};
struct F{};

void print(A) { std::cout << "A"; }
void print(B) { std::cout << "B"; }
void print(C) { std::cout << "C"; }
void print(D) { std::cout << "D"; }
void print(E) { std::cout << "E"; }
void print(F) { std::cout << "F"; }


template <typename ...Args> struct typelist { };

template<typename... Args>
void print(typelist<Args...>)
{
    std::cout << '[';
    int x[]{ (print(Args{}), 0)... };
    std::cout << ']';
    (void)x;
}


template <typename S, typename T> struct typelist_cat;

template <typename ...Ss, typename ...Ts>
struct typelist_cat<typelist<Ss...>, typelist<Ts...>>
{
    typedef typelist<Ss..., Ts...> type;
};


template <typename S, typename T> struct product;

template <typename S, typename ...Ss, typename ...Ts>
struct product<typelist<S, Ss...>, typelist<Ts...>>
{
    typedef typename typelist_cat<typelist<S, Ts...>,
       typename product<typelist<Ss...>, typelist<Ts...>>::type>::type type;
    // try this and the one below:
    //typedef typename typelist_cat<typelist<typelist<S, Ts>...>,
    //   typename product<typelist<Ss...>, typelist<Ts...>>::type>::type type;
};

template <typename S, typename ...Ts>
struct product<typelist<S>, typelist<Ts...>>
{
    typedef typelist<S, Ts...> type;
    // try this and the one above:
    //typedef typelist<typelist<S, Ts>...> type;
};


template<class T>
void pretty_print_type()
{
    std::cout << __PRETTY_FUNCTION__;
}

int main()
{
    using product_type = product<typelist<A,B,C>, typelist<D,E,F>>::type;
    pretty_print_type<product_type>();
    std::cout << '\n';
    print( product_type{} );
}