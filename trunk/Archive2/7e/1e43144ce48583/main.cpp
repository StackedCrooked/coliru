#include<iostream>

template<typename T>
struct TD; //type display

template<typename FunctionType, typename T, typename ... Ts>
struct ArgumentDeduction
{
    typedef typename std::conditional<std::is_same<void, typename std::result_of<FunctionType(T)>::type>::value
                                     , T
                                     , typename ArgumentDeduction<FunctionType, Ts ...>::type
                                     >::type type;
};

template<typename FunctionType, typename T>
struct ArgumentDeduction<FunctionType, T>
{
    typedef typename std::conditional<std::is_same<void, typename std::result_of<FunctionType(T)>::type>::value
                                     , T
                                     , void
                                     >::type type;    
};


template<typename FunctionType
       , typename T = typename ArgumentDeduction<FunctionType, int, double>::type >
void foo()
{
    TD<T>();
}

struct AvoidConversion
{
    struct DummyType{};
    template<typename T> DummyType operator()(T x) { return DummyType(); }    
};

struct Bar : public AvoidConversion
{
    using AvoidConversion::operator();

    //void operator()(int x);
    void operator()(double x);   //try also this
};

int main()
{
    foo<Bar>();  //calls the foo<Bar,int> version

//    auto f=[](double x) {};
//    foo<decltype(f)>();  //calls the foo<Bar,int> version
}
