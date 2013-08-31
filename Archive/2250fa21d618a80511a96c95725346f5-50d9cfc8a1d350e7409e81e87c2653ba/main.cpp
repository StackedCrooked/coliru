#include <tuple> 

template <class T> 
struct Wrapper { T x; }; 

template <class... Types> 
using Tuple = std::tuple<Wrapper<Types>...>; 

template <class... Types> 
struct X 
{ 
    using MyTuple = Tuple<Types...>; 
}; 

int main( int argc, char** argv ) 
{ 
    Tuple<int,int> t;  // (1)
    using Y = X<int,int>;
    Y y;                  // (2)
    return 0; 
}