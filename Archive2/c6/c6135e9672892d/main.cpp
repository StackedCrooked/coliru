#include <functional>
#include <type_traits>
#include <utility>
#include <boost/mpl/not.hpp>

template<typename Compare,typename T>
struct is_exact_compare_helper:Compare
{
  using Compare::operator();
  template<typename Q,typename U>
  void operator()(Q&&,U&&)const;
};

template<typename>
struct void_
{
  typedef void type;
};

template<typename Compare,typename T,typename=void>
struct is_exact_compare:std::true_type{};

template<typename Compare,typename T>
struct is_exact_compare<
  Compare,T,
  typename void_<
    decltype(
        std::declval<const is_exact_compare_helper<Compare,T>>()(
          std::declval<const T&>(),std::declval<const T&>()))
  >::type
>:
  boost::mpl::not_<std::is_void<
    decltype(
      std::declval<const is_exact_compare_helper<Compare,T>>()(
        std::declval<const T&>(),std::declval<const T&>()))
  >>
{};

#include <iostream>

struct univ_less
{
  template<typename Q,typename U>
  bool operator()(Q,U)const;
};

int main()
{
  std::cout<<is_exact_compare<std::less<int>,int>::value<<"\n";
  std::cout<<is_exact_compare<std::less<int>,char>::value<<"\n";
  std::cout<<is_exact_compare<std::less<void*>,char>::value<<"\n";
  std::cout<<is_exact_compare<std::less<>,char>::value<<"\n";
  std::cout<<is_exact_compare<univ_less,char>::value<<"\n";
}