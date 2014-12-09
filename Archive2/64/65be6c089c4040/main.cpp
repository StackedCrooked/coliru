#include <iostream>
#include <typeinfo>

template<int ... Values>
struct List
{
    static void print()
    {
        auto vals = { Values... };
        for (auto && i : vals)
            std::cout << i << " ";
        std::cout << std::endl;
    }
};

template<int X, typename List> 
struct PushBack;

template<int X, int ... Values>
struct PushBack<X, List<Values...>>
{
    using type = List<Values..., X>;
};

template<int X, typename List, bool push>
struct PushBackIf;

template<int X, int ... Values>
struct PushBackIf<X, List<Values...>, true>
{
    using type = typename PushBack<X, List<Values...>>::type;
};

template<int X, int ... Values>
struct PushBackIf<X, List<Values...>, false>
{
    using type = List<Values...>;
};

template<int X, typename List, template <int> class MyPred>
struct FilteredPushBack;

template<int X, int ... Values, template <int> class MyPred>
struct FilteredPushBack<X, List<Values...>, MyPred>
{
    using type = typename PushBackIf< X, List<Values...>, MyPred<X>::value >::type;
};

template<typename Src, typename Dst, template<int> class MyPred>
struct _FilterList;

template<int X, int ... Vals1, int ... Vals2, template<int> class MyPred>
struct _FilterList<List<X, Vals1...>, List<Vals2...>, MyPred>
{
    using type = typename _FilterList<List<Vals1...>, typename FilteredPushBack<X, List<Vals2...>, MyPred>::type, MyPred>::type;
};

template<int X, int ... Vals2, template<int> class MyPred>
struct _FilterList<List<X>, List<Vals2...>, MyPred>
{
    using type = typename FilteredPushBack<X, List<Vals2...>, MyPred>::type;
};

template <typename List, template<int> class MyPred>
struct FilterList;

template <int ... Values, template<int> class MyPred>
struct FilterList<List<Values...>, MyPred>
{
  using type = typename _FilterList<List<Values...>, List<>, MyPred>::type;
};

template<int c>
struct Generate
{
    using type = typename PushBack<c, typename Generate<c-1>::type>::type;
};

template<> 
struct Generate<0>
{
    using type = List<0>;
};

////////////////////////////// Predicates //////////////////////////////
template<typename List>
struct Pop2Front;

template<int X, int Y, int ... Values>
struct Pop2Front<List<X, Y, Values...>>
{
    using type = List<Values...>;
};

template <int X, typename DivList>
struct _IsPrime;

template<int X, int D, int ... Divisors>
struct _IsPrime<X, List<D, Divisors...>>
{
  static const bool value = (X % D != 0) && _IsPrime<X, List<Divisors...>>::value;  
};

template<int X, int D>
struct _IsPrime<X, List<D>>
{
  static const bool value = (X % D != 0);  
};

template<int X>
struct IsPrime
{
  static const bool value = _IsPrime<X, typename Pop2Front<typename Generate<X-1>::type>::type>::value;
};

template<>
struct IsPrime<0>
{
    static const bool value = false;
};

template<>
struct IsPrime<1>
{
    static const bool value = false;
};

template<>
struct IsPrime<2>
{
    static const bool value = true;
};

int main()
{
    FilterList<Generate<100>::type, IsPrime>::type::print();
}
