#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <iterator>
#include <stdexcept>

template< typename Rval, typename ... Args> 
struct Functor;

template<typename T>
struct ParamGenerator
{
    T get(){return T();};  
};

template<>
struct ParamGenerator<int>
{
    int get(){return 42;};
};

template<>
struct ParamGenerator<float>
{
    float get(){return 3.14;};
};

template<>
struct ParamGenerator<bool>
{
    bool get(){return true;};
};

template<typename First, typename ... Rest>
struct apply
{  
    apply(Functor<First, Rest ...> fn){this->fn = fn;};
    Functor<First, Rest ...> fn;
    template<typename ... Before, typename After>
    void call(Before ... param, After after);
    void call();
    
};

template< typename First, typename ... Rest> 
struct Functor
{
    apply<First, Rest...> gen_apply(){return apply<First, Rest ...>(*this);};
};

template<typename First, typename ... Rest>
template<typename ... Before, typename After>
void apply<First, Rest ...>::call(Before ... param, After after)
{
    std::cout << sizeof...(Rest) << std::endl;
    std::cout << sizeof...(Before) << std::endl;
    
}

template<typename First, typename ... Rest>
void apply<First, Rest ...>::call()
{
    std::cout << "0 paramcall" << std::endl;
    auto tu = (std::make_tuple(Rest()...));
    auto tu_size = sizeof ... (Rest);
}



int main()
{
    std::cout << "test begin" << std::endl;
    
    auto fn = Functor<int, int, bool, float>();
    auto app = fn.gen_apply();
    app.call();
    
    return 0;
}