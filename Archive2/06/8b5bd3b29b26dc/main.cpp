#include <iostream>
#include <typeinfo>
#include <type_traits>
#include <algorithm>
#include <iterator>
#include <iomanip>


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


template <>                        // еще один костыль для VC, должно быть: template <typename T>
struct is_empty_<list_t<int> >  //list_t<T>
{
  static const bool value = true;
};

template <>                    	   
struct is_empty_<list_t<size_t> >  
{
  static const bool value = true;
};

template <>
struct is_empty_<list_t<char> >
{
  static const bool value = true;
};

//////////////////////////////////////////////////////////////////
//  Пустой список того же типа
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
  std::cout << ilist;
}

template <template <typename T, T...> class List, typename T, T ... Xs >
auto printn(const List<T, Xs...> &) -> std::enable_if_t< is_empty_<List<T, Xs...>>::value >
{
  std::cout << std::endl;
}

template<typename T>
std::ostream & operator<<(std::ostream & os, const std::initializer_list<T> & list)
{
  return std::copy(std::begin(list), std::end(list), std::ostream_iterator<T>(std::cout, " ")), os;
}

template <typename T, T ... Xs >
std::ostream & operator<<(std::ostream & os, const list_t<T, Xs...> & list)
{
  ::printn(list);
  return os;
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

template <typename T, T left, T right>
struct less_
{
  static const bool value = left < right;
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

template <typename P>
struct notf_
{
  template <typename T, T left, T right>
  using pred = typename P:: template type<T, left, right>;

  template <typename T, T left, T right>
  using type = typename not_< pred >:: template type<T, left, right>;
};

//////////////////////////////////////////////////////////////////
//  Слияние списков
//////////////////////////////////////////////////////////////////

template < typename L1, typename L2, typename L3 >
struct merge_;

template < template <typename T, T...> class List, typename T, T ...Xs1, T ...Xs2, T ...Xs3>
struct merge_<List<T, Xs1...>, List<T, Xs2...>, List<T, Xs3...>>
{
  using type = List<T, Xs1..., Xs2..., Xs3...>;
};

template < typename L1, typename L2, typename L3 >
using merge_t = typename merge_<L1, L2, L3>::type;


//////////////////////////////////////////////////////////////////
//  Сортировка
//////////////////////////////////////////////////////////////////

template <typename List, typename Pred>
struct qsort_;

template <typename List, typename Pred>
struct qsort__;

template < template<typename T, T...> class List, typename T, T X, T ...Xs, typename Pred>
struct qsort_<List<T, X, Xs...>, Pred>
{
  using type = merge_t<
    typename qsort__< filtered_t< List<T, Xs...>, bind2__< Pred::template type, int, X> >, Pred >::type::type
    , List<T, X>
    , typename qsort__< filtered_t< List<T, Xs...>, bind2__< notf_<Pred>::template type, int, X> >, Pred >::type::type
  >;
};

// костыль для MSVC
template <typename List, typename Pred>
struct qsort__
{
  using type = typename
    std::conditional_t< is_empty_<List>::value
    , identity_<List>
    , qsort_< List, Pred >
    >;
};


int main()
{
  ::setlocale(0, "");

  using list = list_t<int, 78, 100, 42, 0, 45, -17, 55, -87, 97>;

  using result_g = qsort__< list, function_<greater_> >::type::type;
  using result_l = qsort__< list, function_<less_> >::type::type;

  std::cout << std::setw(30) << std::left << "исходный список: "            << list {} << std::endl;
  std::cout << std::setw(30) << std::left << "сортировка по возрастанию: "  << result_g {} << std::endl;
  std::cout << std::setw(30) << std::left << "сортировка по убыванию: "     << result_l {} << std::endl;

  return EXIT_SUCCESS;
}