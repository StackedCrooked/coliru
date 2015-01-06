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
    template<int index, typename ... Params>
    void call(Params ... params);
    void call();
    template<typename T>
    T getParam();
    
    template<int index, typename T>
    T getParamRoot(T param);
    
};

template< typename First, typename ... Rest> 
struct Functor
{
    apply<First, Rest...> gen_apply(){return apply<First, Rest ...>(*this);};
};

template<typename First, typename ... Rest>
template<int index, typename ... Params>
void apply<First, Rest ...>::call(Params ... params)
{
    
    if (sizeof...(Params) == sizeof...(Rest))
    {
        std::cout << "get full params" << sizeof...(Params) << std::endl;
    }
    else
    {
        auto tu = (std::make_tuple(Rest()...));
        auto t = std::get<index>(tu);
        auto param = this->getParamRoot<index>(std::get<index>(tu));
        std::cout << index << std::endl;
        std::cout << param << std::endl;
        //this->call<index + 1>(...params, param);
        
        
    }
    
}

template<typename First, typename ... Rest>
void apply<First, Rest ...>::call()
{
    std::cout << "0 paramcall" << std::endl;
    auto tu = (std::make_tuple(Rest()...));
    auto tu_size = sizeof ... (Rest);
    
    std::cout << std::get<0>(tu) << std::endl;
    std::cout << this->getParamRoot<0>(std::get<0>(tu));
    this->call<0>();
    // std::cout << delctype(std::get<0>(tu)) << std::endl;
    // 0的时候，应该去call一个index是1的方法
}

template<typename First, typename ... Rest>
template<typename T>

T apply<First, Rest ...>::getParam()
{
   auto pg = ParamGenerator<T>();
   return pg.get();
}


template<typename First, typename ... Rest>
template<int index, typename T>

T apply<First, Rest ...>::getParamRoot(T param)
{
   return this->getParam<T>();
}

int main()
{
    std::cout << "test begin" << std::endl;
    
    auto fn = Functor<int, int, bool, float>();
    auto app = fn.gen_apply();
    app.call();
    
    return 0;
}