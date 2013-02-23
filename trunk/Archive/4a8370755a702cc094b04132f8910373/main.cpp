#include <type_traits>

template<class T> using Invoke = typename T::type;
template<class T> using AddConst = Invoke<std::add_const<T>>;
template<class T> using AddVolatile = Invoke<std::add_volatile<T>>;
template<class T> using AddLvalueRef = Invoke<std::add_lvalue_reference<T>>;
template<class T> using AddRvalueRef = Invoke<std::add_rvalue_reference<T>>;
template<bool B, class T, class F> using If = Invoke<std::conditional<B, T, F>>;

// ^ standard stuff
///////////////////////////////////////////////
// v implementation

namespace rank_detail{
typedef int second;
typedef long third;

struct first{ operator second(){ return {}; } };

template<unsigned I, class T>
struct qualify{
  using _ctype = If<I % 4 != 0, AddConst<T>, T>;
  using _cvtype = If<I % 4 == 2, AddVolatile<_ctype>, _ctype>;
  using type = If<I % 4 == 3, AddLvalueRef<_cvtype>, AddRvalueRef<_cvtype>>;
};

template<unsigned I, class T>
using RankQualify = Invoke<qualify<I, T>>;

template<unsigned I>
using Rank = RankQualify<I, If<I < 4, first, If<I < 8, second, third>>>;

inline first select_overload(){ return {}; }

static_assert(std::is_same<Rank<0>,  first&&>{}, "rank 0");
static_assert(std::is_same<Rank<1>,  first const&&>{}, "rank 1");
static_assert(std::is_same<Rank<2>,  first const volatile&&>{}, "rank 2");
static_assert(std::is_same<Rank<3>,  first const&>{}, "rank 3");
static_assert(std::is_same<Rank<4>,  second&&>{}, "rank 4");
static_assert(std::is_same<Rank<5>,  second const&&>{}, "rank 5");
static_assert(std::is_same<Rank<6>,  second const volatile&&>{}, "rank 6");
static_assert(std::is_same<Rank<7>,  second const&>{}, "rank 7");
static_assert(std::is_same<Rank<8>,  third&&>{}, "rank 8");
static_assert(std::is_same<Rank<9>,  third const&&>{}, "rank 9");
static_assert(std::is_same<Rank<10>, third const volatile&&>{}, "rank 10");
static_assert(std::is_same<Rank<11>, third const&>{}, "rank 11");
} // rank_detail::

using rank_detail::RankQualify;
using rank_detail::Rank;
using rank_detail::select_overload;

// ^ implementation
///////////////////////////////////////////////
// v testing

void foo(Rank<0>);
void foo(Rank<1>);
void foo(Rank<2>);
void foo(Rank<3>);
void foo(Rank<4>);
void foo(Rank<5>);
void foo(Rank<6>);
void foo(Rank<7>);
void foo(Rank<8>);
void foo(Rank<9>);
void foo(Rank<10>);
void foo(Rank<11>);
void foo(...);

int main(){
  foo(select_overload());
}