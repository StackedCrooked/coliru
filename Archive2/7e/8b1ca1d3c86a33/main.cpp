#include <tuple>

template<typename T>
struct Flat
{
    using type=T;
};

template <template<typename...> class C, typename... ARGS0,typename...ARGS1,typename ...ARGS2>
struct Flat< C<ARGS0...,C<ARGS1...>,ARGS2...> >
  : Flat< C<ARGS0...,ARGS1...,ARGS2...> >
{
};

int main(){
    typedef std::tuple<int,std::tuple<int,long>,int> tup;
    static_assert(std::is_same<typename Flat<tup>::type,std::tuple<int,int,long,int> >::value,"");
}
