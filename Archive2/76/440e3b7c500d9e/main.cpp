template<typename... Ts> struct type_list { enum { size = sizeof...(Ts) }; };



#include <array>

template<typename TL>
struct pop
{
    using head = type_list<>;
    using tail = type_list<>;
    enum { size = 0 };
};

template<typename Head, typename... Tail>
struct pop<type_list<Head, Tail...>>
{
    using head = Head;
    using tail = type_list<Tail...>;
    enum { size = 1 + sizeof...(Tail) };
};

template<typename TL, typename T>
struct push;

template<typename... Ts, typename T>
struct push<type_list<Ts...>, T>
{
    using type = type_list<Ts..., T>;
};

template<typename TL>
using Tail = typename pop<TL>::tail;

template<typename TL>
using Head = typename pop<TL>::head;

template<typename TL>
int Size = pop<TL>::size;

template<typename TL, typename T>
using Push = typename push<TL, T>::type;


template<typename T, typename... Ts>
std::array<T, 1+sizeof...(Ts)>
make_array(T t, Ts... ts)
{ return {{t, ts...}}; }

template<typename F, typename... CreatedTypes>
auto generate_lut(type_list<>, type_list<>, type_list<CreatedTypes...>)
{
    return &F::template fun<CreatedTypes...>;
}

template<typename F, typename... MyTypes, typename RemainingTLTL, typename CreatedTypesTL>
auto generate_lut(type_list<MyTypes...>, RemainingTLTL, CreatedTypesTL)
{
    return make_array( generate_lut<F>(Head<RemainingTLTL>{}, Tail<RemainingTLTL>{}, Push<CreatedTypesTL, MyTypes>{})... );
}


#include <iostream>

struct F
{
    template<typename T0, typename T1, typename T2>
    static void fun(char const* str)
    {
        std::cout << __PRETTY_FUNCTION__ << " : " << str << "\n";
    }
};


template<class T>
void print_type() { std::cout << __PRETTY_FUNCTION__ << "\n"; }

int main()
{
    struct A {};
    struct B {};
    struct C {};
    
    using param0 = type_list<A, B, C>;
    using param1 = type_list<B, C, A>;
    using param2 = type_list<C, B, A>;
    
    auto lut = generate_lut<F>(param0{}, type_list<param1, param2>{}, type_list<>{});
    
    for(int a = 0; a < 3; ++a)
        for(int b = 0; b < 3; ++b)
            for(int c = 0; c < 3; ++c)
                lut[a][b][c]("hello world");
}