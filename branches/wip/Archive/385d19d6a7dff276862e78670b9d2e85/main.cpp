#include <type_traits>

template<class T> using Invoke = typename T::type;
template<class T> using AddConst = Invoke<std::add_const<T>>;
template<class T> using AddVolatile = Invoke<std::add_volatile<T>>;
template<bool B, class T, class F> using If = Invoke<std::conditional<B, T, F>>;

// ^ standard stuff
///////////////////////////////////////////////
// v implementation


namespace rank_detail{
struct second{};
struct first{ second _; operator second&(){ return _; } };

template<unsigned I, class T>
struct qualify{
  using _ctype = If<I % 3 != 0, AddConst<T>, T>;
  using type = If<I % 3 == 2, AddVolatile<_ctype>, _ctype>&;
};

struct default_tag;

template<unsigned I, class T>
using RankQualify = Invoke<qualify<I, T>>;

template<unsigned I, class = default_tag>
using Rank = RankQualify<I, If<I < 3, first, second>>;

static_assert(std::is_same<Rank<0>, first&>{}, "rank 0");
static_assert(std::is_same<Rank<1>, first const&>{}, "rank 1");
static_assert(std::is_same<Rank<2>, first const volatile&>{}, "rank 2");
static_assert(std::is_same<Rank<3>, second&>{}, "rank 3");
static_assert(std::is_same<Rank<4>, second const&>{}, "rank 4");
static_assert(std::is_same<Rank<5>, second const volatile&>{}, "rank 5");
} // rank_detail::

template<unsigned I, class T> using RankQualify = rank_detail::RankQualify<I, T>;
template<unsigned I, class Tag = rank_detail::default_tag> using Rank = rank_detail::Rank<I, Tag>;
namespace { rank_detail::first select_overload; }

// ^ implementation
///////////////////////////////////////////////
// v testing

void foo(Rank<0>, Rank<0>);
void foo(Rank<1>, Rank<0>);
void foo(Rank<2>, Rank<0>);
void foo(Rank<3>, Rank<0>);
void foo(Rank<4>, Rank<0>);
void foo(Rank<5>, Rank<0>);
void foo(Rank<0>, Rank<1>);
void foo(Rank<1>, Rank<1>);
void foo(Rank<2>, Rank<1>);
void foo(Rank<3>, Rank<1>);
void foo(Rank<4>, Rank<1>);
void foo(Rank<5>, Rank<1>);
void foo(...);

int main(){
  foo(select_overload);
}