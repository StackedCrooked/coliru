#include <tuple>
#include <iostream>
#include <functional>
#include<utility>
using namespace std;

// Compile with : g++ -o X.bin -Wall -pedantic -std=c++11 X.cpp 

// Stuff for compile-time recursive parameter pack expansion:
namespace generic
{
    template <std::size_t... Ts>
    struct index_sequence {}; 

    template <std::size_t N, std::size_t... Ts>
    struct sequence_generator : sequence_generator<N - 1, N - 1, Ts...> {};

    template <std::size_t... Ts>
    struct sequence_generator<0, Ts...> : index_sequence<Ts...> {};

    template<  typename ReturnType , typename... Args  > using generic_function_pointer = ReturnType (*) (  Args... args  ) ;

}


// The generic Function wrapper: 
template < typename R , class F , typename... Ps>
class gen_func
{
    public:
        // Constructor
        gen_func(F&& f,Ps&&...parms){
            func = forward<F>(f); 
            parameters=make_tuple(forward<Ps>(parms)...);
        }
        // execute-Function for public call:
        template<typename... Vars>
        R execute(Vars&&... vars) { 
           return f_decon<Vars... , Ps...>( forward<Vars>(vars)... , parameters );
        }
        //
    private:
         // "Deconvolution Function"
        template<typename... Vars , typename... Ts >
        R f_decon( Vars&&... vars , tuple<Ts...>& tup ){
            return f_proxy<Vars...,Ps...>( forward<Vars>(vars)... , tup , generic::sequence_generator<sizeof...(Ts)>{} );
        }
        // "Proxy-Function" calling the wrapped Function func:
        template<typename... Vars , typename... Ts , size_t... Is>
        R f_proxy( Vars&&... vars , tuple<Ts...>& tup , generic::index_sequence<Is...> ){
            return func( forward<Vars>(vars)... , get<Is>(tup)... );
        }
        // The wrapped Function f
        F func;
        // The tuple holding optional parameters for function f:
        tuple<Ps...> parameters; 

};

// Partial template Specialization of gen_func for Functions with Return Type void:
template <class F , typename... Ps>
class gen_func<void,F,Ps...>
{
    public:
        // Constructor
        gen_func(F&& f,Ps&&...parms){
            func = forward<F>(f); 
            parameters=make_tuple(forward<Ps>(parms)...);
        }
        // execute-Function for public call:
        template<typename... Vars>
        void execute(Vars&&... vars) { 
           f_decon<Vars... , Ps...>( forward<Vars>(vars)... , parameters );     // Line 75
        }
        //
    private:
        // The wrapped Function f
        F func;
        // The tuple holding optional parameters for function f:
        tuple<Ps...> parameters;
         // "Deconvolution Function"
        template<typename... Vars , typename... Ts >                            
        void f_decon( Vars&&... vars , tuple<Ts...>& tup ){                     // Line 85
            f_proxy<Vars...,Ts...>( forward<Vars>(vars)... , tup , generic::sequence_generator<sizeof...(Ts)>{} );
        }
        // "Proxy-Function" calling the wrapped Function func:
        template<typename... Vars , typename... Ts , size_t... Is>
        void f_proxy( Vars&&... vars , tuple<Ts...>& tup , generic::index_sequence<Is...> ){
            func( forward<Vars>(vars)... , get<Is>(tup)... );
        }
};

void change(int& m,int n){
    cout << "Changing!" << endl;
    int res=42+n;
    m=res;
}  

int main()
{
    typedef generic::generic_function_pointer<void,int&,int>  chg_ptr;
    
    gen_func<void,chg_ptr> y(change);
    
    // The Variable to be altered by change    
    int j=0;
    cout << "j='" << j << "'" << endl; // should be 0
    // Wrapped Function call:
    y.execute(j,21);                                        // Line 113
    cout << "j='" << j << "'" << endl; // should be 63
    
    return 0;
}  