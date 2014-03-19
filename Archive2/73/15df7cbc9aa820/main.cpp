template<typename... Ts>
struct list {};

template<typename> struct debug;

template<typename INPUT , typename OUTPUT>
struct reverse_impl;


template<typename HEAD , typename... TAIL , typename... Ts>
struct reverse_impl<list<HEAD,TAIL...>,list<Ts...>>
{
    using t=typename debug<reverse_impl>::type;
    using result = typename reverse_impl<list<TAIL...>,list<Ts...,HEAD>>::result;
};

template<typename... Ts>
struct reverse_impl<list<>,list<Ts...>>
{
    using t=typename debug<reverse_impl>::type;
    using result = list<Ts...>;
};

template<typename LIST>
using reverse = typename reverse_impl<LIST,list<>>::result;

using L1=list<int, short, char>;
using rL1=reverse<L1>;

using L2=list<short, char>;
using rL2=reverse<L2>;

int main() {};