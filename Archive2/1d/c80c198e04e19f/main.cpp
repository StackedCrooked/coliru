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


template<typename Src, typename Dest>
struct PopBack_;

template<int X, int ... Xs1, int ... Xs2>
struct PopBack_<List<X,Xs1...>, List<Xs2...>> 
{
    using type = typename PopBack_< List<Xs1...>, List<X, Xs2...>>::type;
};

template<int X, int ... Xs2>
struct PopBack_<List<X>, List<Xs2...>> 
{
    using type = List<Xs2...>;
};

template<typename List>
struct PopBack;

template<int ... Xs>
struct PopBack<List<Xs...>>
{
    using type = typename PopBack_<List<Xs...>, List<>>::type;
};

int main()
{
    PushBack<6,List<3,4,5>>::type::print();
    PopBack<List<3,4,5>>::type::print();
}
