#include <type_traits>

struct X{};
struct Y{ X x; operator X&(){ return x; } };

template<class T> using Invoke = typename T::type;
template<class T> using AddConst = Invoke<std::add_const<T>>;
template<class T> using AddVolatile = Invoke<std::add_volatile<T>>;
template<bool B, class T, class F> using If = Invoke<std::conditional<B, T, F>>;

template<unsigned I, class T>
struct rank_qualify{
  using _ctype = If<I % 3 != 0, AddConst<T>, T>;
  using type = If<I % 3 == 2, AddVolatile<_ctype>, _ctype>&;
};

template<unsigned I, class T> using RankQualify = Invoke<rank_qualify<I, T>>;
template<unsigned I> using Rank = RankQualify<I, If<I < 3, Y, X>>;
namespace { Y select_overload; }

static_assert(std::is_same<Rank<0>, Y&>{}, "rank 0");
static_assert(std::is_same<Rank<1>, Y const&>{}, "rank 1");
static_assert(std::is_same<Rank<2>, Y const volatile&>{}, "rank 2");
static_assert(std::is_same<Rank<3>, X&>{}, "rank 3");
static_assert(std::is_same<Rank<4>, X const&>{}, "rank 4");
static_assert(std::is_same<Rank<5>, X const volatile&>{}, "rank 5");

void foo(Rank<0>);
void foo(Rank<1>);
void foo(Rank<2>);
void foo(Rank<3>);
void foo(Rank<4>);
void foo(Rank<5>);
void foo(...);

int main(){
  foo(select_overload);
}