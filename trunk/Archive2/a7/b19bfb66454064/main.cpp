#include <type_traits>
#include <utility>
#include <iostream>

namespace detail
{

template<typename T>
constexpr auto address(T&& t) ->
  typename ::std::remove_reference<T>::type*
{
  return &t;
}

template<class Fp, Fp fp, class C, class... A>
struct helper_fo
{
    C* object;
    auto operator()(A&&... args)
    -> decltype( (object->*fp)(::std::forward<A>(args)...) )
    {
        return (object->*fp)(::std::forward<A>(args)...);
    }
};

template<class Fp, Fp fp, class C, class... A>
auto helper_func(C* const object) noexcept
-> helper_fo<Fp, fp, C, A...>
{
  return {object};
};

template <typename FP, FP fp, class C, typename ...A>
struct S
{
  static constexpr auto* l = &helper_func<FP, fp, C, A...>;
};

template <typename FP, FP fp, typename R, class C, typename ...A>
auto make_member_delegate(C* const object, R (C::* const)(A...)) ->
  decltype((*S<FP, fp, C, A...>::l)(object))
{
  return (*S<FP, fp, C, A...>::l)(object);
}

}

template <typename FP, FP fp, class C>
auto make_member_delegate(C* const object) ->
  decltype(detail::make_member_delegate<FP, fp>(object, fp))
{
  return detail::make_member_delegate<FP, fp>(object, fp);
}

struct A
{
  void hello()
  {
    ::std::cout << "it worked" << ::std::endl;
  }
};

int main()
{
  A a;

  auto d(make_member_delegate<decltype(&A::hello), &A::hello>(&a));

  d();

  return 0;
}