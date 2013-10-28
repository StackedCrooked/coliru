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
    // the cartesian product of {S} and {Ts...}
    // is a list of pairs -- here: a typelist of 2-element typelists
    typedef typelist<typelist<S, Ts>...> S_cross_Ts;

    // the cartesian product of {Ss...} and {Ts...} (computed recursively)
    typedef typename product<typelist<Ss...>, typelist<Ts...>>::type
        Ss_cross_Ts;

    // concatenate both products
    typedef typename typelist_cat<S_cross_Ts, Ss_cross_Ts>::type type;
};

// end the recursion
template <typename ...Ts>
struct product<typelist<>, typelist<Ts...>>
{
    typedef typelist<> type;
};


template<class T>
void pretty_print_type()
{
    std::cout << __PRETTY_FUNCTION__;
}

int main()
{
    using product_type_1 = product<typelist<A,B>, typelist<D,E,F>>::type;
    pretty_print_type<product_type_1>();
    
    std::cout << "\n\n";
    
    using product_type_2 = product<typelist<>, typelist<D,E,F>>::type;
    pretty_print_type<product_type_2>();
    
    std::cout << "\n\n";
    
    using product_type_2 = product<typelist<A,B,C>, typelist<>>::type;
    pretty_print_type<product_type_2>();
}