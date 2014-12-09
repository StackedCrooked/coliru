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

template<typename List>
struct PopBack;

template<int X, int ... Values>
struct PopBack<List<Values...,X>> 
{
    static const int removed = X;
    using type = List<Values...>;
};


int main()
{
    PushBack<6,List<3,4,5>>::type::print();
    PopBack<List<3,4,5>>::type::print();
}
