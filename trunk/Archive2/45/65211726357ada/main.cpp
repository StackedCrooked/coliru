template<typename... Ts>
struct list {};

template<typename> struct debug;

template<typename, typename> 
struct concat_impl;

template<typename... T1, typename... T2>
struct concat_impl<list<T1...>, list<T2...>>
{
    using type=list<T1..., T2...>;
};

template<typename T1, typename T2>
using concat = typename concat_impl<T1,T2>::type;


template<typename LIST>
struct reverse_impl;


template<typename HEAD , typename... TAIL>
struct reverse_impl<list<HEAD,TAIL...>>
{
 
    using t=typename debug<reverse_impl>::type;
    using type = concat<typename reverse_impl<list<TAIL...>>::type,list<HEAD>>;
};

template<>
struct reverse_impl<list<>>
{
    using type = list<>;
};

template<typename T>
using reverse = typename reverse_impl<T>::type;

using L1=list<int, short, char>;
using rL1=reverse<L1>;

using L2=list<short, char>;
using rL2=reverse<L2>;

int main() {}