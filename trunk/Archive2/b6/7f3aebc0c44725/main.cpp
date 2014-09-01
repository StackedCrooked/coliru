#include <iostream>

using namespace std;

template<size_t ...>
struct lst_{};

template<class _Pred, class _Dest, class _Src>
struct filter_;

template<class...>
struct add_;

template<size_t..._Left, size_t..._Right>
struct add_<lst_<_Left...>, lst_<_Right...>>
{
  using type = lst_<_Left..., _Right...>;
};

template<size_t..._Left, size_t..._Middle, size_t..._Right>
struct add_<lst_<_Left...>, lst_<_Middle...>, lst_<_Right...>>
{
  using type = lst_<_Left..., _Middle..., _Right...>;
};

template<bool _Pred, size_t _Val, size_t ..._Vals>
struct add_if;

template<size_t _Val, size_t ..._Vals>
struct add_if<true, _Val, _Vals...>
{
  using type = lst_<_Vals..., _Val>;
};

template<size_t _Val, size_t ..._Vals>
struct add_if<false, _Val, _Vals...>
{
  using type = lst_<_Vals...>;
};


template<class _Pred, size_t _Val, size_t ..._Vals, size_t ..._ValsD>
struct filter_<_Pred, lst_<_Val, _Vals...>, lst_<_ValsD...>>
{
  using _Cond = typename _Pred::template is<_Val>;

  using vals = typename filter_
               <
               _Pred
               , lst_<_Vals... >
               , typename add_if < ( _Cond::val )
               , _Val, _ValsD... >::type
               >
               ::vals;
};


template<typename _Pred, size_t ..._ValsD>
struct filter_<_Pred, lst_<>, lst_<_ValsD...>>
{
  using vals = lst_<_ValsD...>;
};

template<typename _Pred, class ..._ValsD>
struct filter
{
  using type = typename filter_<_Pred, _ValsD..., lst_<>>::vals;
};

template<size_t _Left, size_t _Right>
struct less_
{
  static const bool val = _Left < _Right;
};

template<size_t _Val>
struct less
{
  template<size_t _Left>
  using is = less_<_Left, _Val>;
};

template<size_t _Left, size_t _Right>
struct greater_eq_
{
  static const bool val = _Left >= _Right;
};

template<size_t _Val>
struct greater_eq
{
  template<size_t _Left>
  using is = greater_eq_<_Left, _Val>;
};

template<class _Holder>
struct qsort_;

template<typename _Ty>
using qsort_t = typename qsort_<_Ty>::type;

template<class _Pred, class _Vals>
using filter_t = typename filter<_Pred, _Vals>::type;

template<class _V1, class _V2, class _V3>
using add_t = typename add_<_V1, _V2, _V3>::type;


template<>
struct qsort_<lst_<>>
{
  using type = lst_<>;
};

template<size_t _H, size_t ..._T>
struct qsort_<lst_<_H, _T...>>
{
  using type =  add_t <
                        qsort_t< filter_t<::less<_H>, lst_<_T...>>>,
                        lst_<_H>,
                        qsort_t< filter_t<::greater_eq<_H>, lst_<_T...>>>
                       >;
};


template<int ... Vals>
void printnl( const lst_<Vals...> &)
{
  for ( auto i : {Vals...} ) cout << i << " ";
  cout << endl;
}

int main()
{
  using list_ = lst_ < 10, 2, 33, 33, 33, 30, 14, 23, 48, 76, 22, 12, 43, 34, 42, 23545, 46367, 45>;

  ::printnl( list_{} );
//  ::printnl( qsort_t< list_ >{} );

  ::getchar();
}