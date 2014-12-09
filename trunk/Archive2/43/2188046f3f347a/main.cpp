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

template<int X>
struct Pred
{
  static const bool value = X % 2 == 0; 
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

template<int X, typename List, typename MyPred>
struct FilteredPushBack;

template<int X, int ... Values, typename MyPred>
struct FilteredPushBack<X, List<Values...>, MyPred<X>>
{
    using type = double;
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


int main()
{
    PushBack<6,List<3,4,5>>::type::print();
    Generate<20>::type::print();
}
