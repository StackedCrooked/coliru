#include <iostream>
#include <typeinfo>
#include <type_traits>
#include <algorithm>
#include <iterator>

template<typename T>
std::ostream & operator<<(std::ostream & os, const std::initializer_list<T> & list)
{
  return std::copy(std::begin(list), std::end(list), std::ostream_iterator<T>(std::cout, " ")), os;
}

//////////////////////////////////////////////////////////////////
// Список значений
//////////////////////////////////////////////////////////////////

template <typename T, T ...>
struct list_t {};


//////////////////////////////////////////////////////////////////
//  костыль для MSVC v120+ (VS2013+)
//////////////////////////////////////////////////////////////////

template<typename T>
struct is_empty_;

template <typename T, T X, T...Xs>
struct is_empty_<list_t<T, X, Xs...> >
{
  static const bool value = false;
};


template <>                    	// еще один костыль для VC, должно быть: template <typename T>
struct is_empty_<list_t<int> >  //list_t<T>
{
  static const bool value = true;
};


//////////////////////////////////////////////////////////////////
//  Для работы со списком
//////////////////////////////////////////////////////////////////

template <typename T>
struct get_empty_;

template <template <typename T, T...> class List, typename T, T ... Xs>
struct get_empty_<List<T, Xs...>>
{
  using type = List<T>;
};

template <typename T>
using get_empty_t = typename get_empty_<T>::type;


//////////////////////////////////////////////////////////////////
//  Утилиты
//////////////////////////////////////////////////////////////////

template <template <typename T, T, T> class F, typename T, T left>
struct bind2__
{
  template<T right>
  using apply = F<T, right, left>;
};

template <template <typename T, typename Pred> class F, typename A, typename Pred>
struct bind_
{
  using type = F<A, Pred>;
};

template<class T>
struct identity_
{
  using type = T;
};

template <template <typename T, T, T> class F>
struct function_
{
  template<typename T, T right, T left>
  using type = F<T, left, right>;
};


//////////////////////////////////////////////////////////////////
//  Вывод значений
//////////////////////////////////////////////////////////////////

template <template <typename T, T...> class List, typename T, T X, T ... Xs>
auto printn(const List<T, X, Xs...> &) -> std::enable_if_t< !is_empty_<List<T, X, Xs...>>::value >
{
  auto ilist = { X, Xs... };
  std::cout << ilist << std::endl;
}

template <template <typename T, T...> class List, typename T, T ... Xs >
auto printn(const List<T, Xs...> &) -> std::enable_if_t< is_empty_<List<T, Xs...>>::value >
{
  std::cout << std::endl;
}


//////////////////////////////////////////////////////////////////
//  Фильтр
//////////////////////////////////////////////////////////////////

template<typename Left, typename Right, typename Pred>
struct filter_{};

template <template <typename T, T...> class List, typename T, T X, T ... Xs, T ... Xs2, typename Pred>
struct filter_<List<T, X, Xs...>, List<T, Xs2...>, Pred>
{
  using filtered_ =
    std::conditional_t <
    Pred::template apply<X>::value
    , List<T, X, Xs2...>
    , List<T, Xs2...> >;

  using type = typename filter_< List<T, Xs...>, filtered_, Pred >::type;
};

template <template <typename T, T...> class List, typename T, T X, T ... Xs2, typename Pred>
struct filter_< List<T, X>, List<T, Xs2...>, Pred>
{
  using filtered_ =
    std::conditional_t <
    Pred::template apply<X>::value
    , List<T, X, Xs2...>
    , List<T, Xs2...> >;

  using type = filtered_;
};

template <class List, typename Pred>
using filter_t = typename filter_<List, typename get_empty_<List>::type, Pred>::type;

template <typename T, typename Pred>
struct filtered_
{
  using type = std::conditional_t< is_empty_<T>::value, identity_<T>, bind_<filter_t, T, Pred>>;
};

template <class List, typename Pred>
using filtered_t = typename filtered_<List, Pred>::type::type;


//////////////////////////////////////////////////////////////////
//  Предикаты
//////////////////////////////////////////////////////////////////

template <typename T, T left, T right>
struct greater_
{
  static const bool value = left > right;
};

template <template <typename T, T, T> class F>
struct not_
{
  template<typename T, T left, T right>
  struct type
  {
    static const bool value = !F<T, left, right>::value;
  };
};


template < typename L1, typename L2, typename L3 >
struct merge_;

template < template <typename T, T...> class List, typename T, T ...Xs1, T ...Xs2, T ...Xs3>
struct merge_<List<T, Xs1...>, List<T, Xs2...>, List<T, Xs3...>>
{
  using type = List<T, Xs1..., Xs2..., Xs3...>;
};

template < typename L1, typename L2, typename L3 >
using merge_t = typename merge_<L1, L2, L3>::type;


template <typename List, typename Pred>
struct qsort_;

template < template<typename T, T...> class List, typename T, T X, T ...Xs, typename Pred>
struct qsort_<List<T, X, Xs...>, Pred>
{
  using type = filtered_t< List<T, Xs...>, bind2__<Pred::template type, int, X> >;
};

template < template<typename T, T...> class List, typename T, T ...Xs, typename Pred>
struct qsort_<List<T, Xs...>, Pred>
{
  using type = List<T, Xs...>;
};

int main()
{
  //std::cout << std::boolalpha <<
  //  is_empty_<list_t<int, 42, 54, 78>>::value
  //  << std::endl;

  //std::cout << std::boolalpha <<
  //  is_empty_<list_t<int>>::value
  //  << std::endl;

  //::printn(list_t<int>{});
  //::printn(list_t<int, 42, 54, 78>{});

  //using type = list_t<int, 15, 75, 5, -45, 78>;
  //using filtered = filtered_t<type, bind2__<greater_, int, 10> >;
  ////using filtered = filtered_t<type, bind2__< not_<greater_>::type, int, 10> >;


  //::printn(type {});
  //::printn(filtered {});

  //std::cout << std::boolalpha <<
  //  bind2__<greater_, int, 100>::apply<20>::value
  //  << std::endl;

  //std::cout << std::boolalpha <<
  //  (bind2__< not_<greater_>::type, int, 100>::apply<20>::value)
  //  << std::endl;


  //::printn(merge_t<list_t<int, 15>, list_t<int, 78>, list_t<int>>{});

  
  //::printn(qsort_< list_t<int, 15, 42, -9, 11>, function_<not_<greater_>::type> >::type {});
  
  //::printn(qsort_< list_t<int>, function_<greater_> >::type {});


  using type = list_t<int,  78>;

  using result =
  std::conditional_t< is_empty_<type>::value
    , identity_<type>
    , qsort_< type, function_<greater_> >
  >::type;

  ::printn(result {});


}