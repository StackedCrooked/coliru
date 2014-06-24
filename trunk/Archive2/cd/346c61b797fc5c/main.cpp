// TS 23.06.2014

#include <tuple>
#include <typeinfo>
#include <utility>

namespace details
{

template <typename A, typename B, typename Enable = void>
struct GetBaseType
{
  using type = typename std::tuple<A>;
};

template <typename A, typename B>
struct GetBaseType<A, B, typename std::enable_if<std::is_base_of<B, A>::value>::type>
{
  using type = typename std::tuple<B>;
};

template <typename...>
struct OneRunShift;

template <typename A>
struct OneRunShift<A>
{
  using type = std::tuple<A>;
};

template <typename First, typename Second, typename... Args>
struct OneRunShift<First, Second, Args...>
{
  using type = decltype(std::tuple_cat(
      std::declval<typename GetBaseType<First, Second>::type>(),
      std::declval<typename OneRunShift<
        typename std::conditional<std::is_base_of<Second, First>::value, First, Second>::type,
        Args...
    >::type>()));
};

template <unsigned, unsigned, typename>
struct HierarchyAlignDet;

template <unsigned Start, unsigned Size, typename... Args>
struct HierarchyAlignDet<Start, Size, std::tuple<Args...>>
{
  using type = typename HierarchyAlignDet<
      Start + 1, 
      Size, 
      typename OneRunShift<Args...>::type
    >::type;
};

template <unsigned End, typename... Args>
struct HierarchyAlignDet<End, End, std::tuple<Args...>>
{
  using type = typename OneRunShift<Args...>::type;
};

} //namespace details

template <typename... Args>
struct HierarchyAlign
{
  using type = typename details::HierarchyAlignDet<
      1,
      sizeof...(Args),
      typename details::OneRunShift<Args...>::type
    >::type;
};

/****************************************************************************/
#define STATIC_CHECK(test) static_assert(test, #test)

class A {};
class B : A {};
class C : B {};
class D : C {};

int main()
{
  STATIC_CHECK((std::is_same<typename HierarchyAlign<A, C, B, C, B, A>::type, std::tuple<A, A, B, B, C, C>>::value));
  STATIC_CHECK((std::is_same<typename HierarchyAlign<C, B, C, B, A>::type, std::tuple<A, B, B, C, C>>::value));
  STATIC_CHECK((std::is_same<typename HierarchyAlign<A, D, B, C, B, A>::type, std::tuple<A, A, B, B, C, D>>::value));
  STATIC_CHECK((std::is_same<typename HierarchyAlign<D, C, B, A, D>::type, std::tuple<A, B, C, D, D>>::value));
  STATIC_CHECK((std::is_same<typename HierarchyAlign<A, C>::type, std::tuple<A, C>>::value));
  STATIC_CHECK((std::is_same<typename HierarchyAlign<C, A>::type, std::tuple<A, C>>::value));
  STATIC_CHECK((std::is_same<typename HierarchyAlign<A, A, A>::type, std::tuple<A, A, A>>::value));
}