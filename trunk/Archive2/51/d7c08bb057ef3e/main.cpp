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
           return f_decon( parameters, forward<Vars>(vars)... );
        }
        //
    private:
         // "Deconvolution Function"
        template<typename... Vars , typename... Ts >
        R f_decon( tuple<Ts...>& tup, Vars&&... vars ){
            return f_proxy( tup , generic::sequence_generator<sizeof...(Ts)>{}, forward<Vars>(vars)... );
        }
        // "Proxy-Function" calling the wrapped Function func:
        template<typename... Vars , typename... Ts , size_t... Is>
        R f_proxy( tuple<Ts...>& tup , generic::index_sequence<Is...>, Vars&&... vars ){
            return func( forward<Vars>(vars)... , get<Is>(tup)... );
        }
        // The wrapped Function f
        F func;
        // The tuple holding optional parameters for function f:
        tuple<Ps...> parameters; 

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