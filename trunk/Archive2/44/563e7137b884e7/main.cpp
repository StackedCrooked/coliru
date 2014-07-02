#include <tuple>
#include <iostream>
using namespace std;

template < typename... Ps>
struct gen_func
{
    tuple<Ps...> parameters;
    
    template<typename... Vars>
    void execute(Vars... vars) { 
       f_decon<Vars...>( vars... , parameters );
    }
    
    template<typename... Vars , typename... Ts >
    void f_decon( Vars... vars , tuple<Ts...> tup )
    {}
};

int main()
{
    gen_func<> y;
    y.execute(42, 'A');
}