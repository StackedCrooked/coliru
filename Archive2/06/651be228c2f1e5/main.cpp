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

template<int X>
struct Even
{
  static const bool value = X % 2 == 0; 
};

template<int X>
struct Odd
{
  static const bool value = !Even<X>::value; 
};

int main()
{
    FilterList<Generate<20>::type, Even>::type::print();
    FilterList<Generate<20>::type, Odd>::type::print();
}
