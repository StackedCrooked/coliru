#include <tuple>

Enum N
{
    Key = 0,
    Value
} ;

template<typename Names, typename Items...>
struct MyTuple{

std::tuple<Items> values;
};

MyTuple<Names, int, int> func()
{
    return make_tuple( N::Key, 10, N::Value, 20 ) ;
}


int main()
{
}