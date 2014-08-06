#include <type_traits>
#include <iostream>
 
template <typename T, typename ...Ts>
struct is_first_arg_const_ptr
{
    template <typename Ret>
    static std::false_type
    is_const(Ret (&f)(T*, Ts...));
 
    template <typename Ret>
    static std::true_type
    is_const(Ret (&f)(const T*, Ts...));

    // And for methods
    template <typename Ret, typename C>
    static std::false_type
    is_const (Ret (C::*) (T*, Ts...)) /* const volatile & && */;

    template <typename Ret, typename C>
    static std::true_type
    is_const (Ret (C::*) (const T*, Ts...)) /* const volatile & && */;
};

template <typename T, typename ...Ts>
constexpr
auto make_is_first_arg_const_ptr(T&& t, Ts&&...)
-> is_first_arg_const_ptr<
    typename std::decay<decltype(*t)>::type,
    typename std::decay<Ts>::type...
>;

#define IS_FIRST_ARG_CONST_PTR(Name, ...) \
    (decltype(make_is_first_arg_const_ptr(__VA_ARGS__).is_const(Name))::value)


class C {};

void fun2(C*) {}
void fun2(const C*, int) {}

struct S
{
    void fun2(C*) {}
    void fun2(const C*, int) {}
};

static_assert(!decltype(is_first_arg_const_ptr<C>::is_const(fun2))::value, "");
static_assert(decltype(is_first_arg_const_ptr<C, int>::is_const(fun2))::value, "");
static_assert(decltype(is_first_arg_const_ptr<C, int>::is_const(&S::fun2))::value, "");

//----------------------------------------------
// Same with template arguments.

template<typename Pix, unsigned Dim>
class D {};

template<typename Pix, unsigned Dim>
void fun3(D<Pix, Dim>*) {}

template<typename Pix, unsigned Dim>
void fun3(const D<Pix, Dim>*, int) {}

struct R
{
  template<typename Pix, unsigned Dim>
  void fun3(D<Pix, Dim>*) {}

  template<typename Pix, unsigned Dim>
  void fun3(const D<Pix, Dim>*, int) {}
};

static_assert(!decltype(is_first_arg_const_ptr<D<float, 2> >::is_const(fun3<float, 2>))::value, "");
static_assert(decltype(is_first_arg_const_ptr<D<float, 2>, int>::is_const(fun3<float, 2>))::value, "");
static_assert(decltype(is_first_arg_const_ptr<D<float, 2>, int>::is_const(&R::fun3<float, 2>))::value, "");


int main ()
{
  C c;
  int a = 42;

  static_assert(!IS_FIRST_ARG_CONST_PTR(fun2, &c), "");
  static_assert(IS_FIRST_ARG_CONST_PTR(fun2, &c, a), "");
  static_assert(IS_FIRST_ARG_CONST_PTR(&S::fun2, &c, a), "");

//  D<float, 2> d;

//  static_assert(!IS_FIRST_ARG_CONST_PTR(fun3<float, 2>, &d), "");
//  static_assert(IS_FIRST_ARG_CONST_PTR(fun3<float, 2>, &d, a), "");
//  static_assert(IS_FIRST_ARG_CONST_PTR(&R::fun3<float, 2>, &d, a), "");

  return 0;
}

