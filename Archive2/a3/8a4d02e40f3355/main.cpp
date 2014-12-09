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

template<int X, typename List, template <int> class MyPred>
struct FilteredPushBack;

template<int X, int ... Values, template <int> class MyPred>
struct FilteredPushBack<X, List<Values...>, MyPred>
{
    using type = typename PushBackIf< X, List<Values...>, MyPred<X>::value >::type;
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
    using data_t = List <10, 20, 49>;
    FilteredPushBack<10, data_t, Pred>::type::print();
    
    PushBack<6,List<3,4,5>>::type::print();
    Generate<20>::type::print();
}
