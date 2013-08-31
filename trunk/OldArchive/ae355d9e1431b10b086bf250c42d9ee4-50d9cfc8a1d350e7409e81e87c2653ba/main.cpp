#include <functional>
#include <iostream>
#include <tuple>


template<typename Signature>
struct Command
{
};


template<typename Result, typename ...Args>
constexpr std::size_t arity(const Command<Result(Args...)>&)
{
    return sizeof...(Args);
}


template<typename Result, typename ...Args>
std::tuple<Args...> MakeTuple(const Command<Result(Args...)>&)
{
    return std::declval<std::tuple<Args...>>();
};


using GetTime = Command<int()>;
using SetTime = Command<void(int)>;
using Sum = Command<int(int, int)>;

typedef int x;
typedef int y;
using Distance = Command<int(x, y, x, y)>;

int main()
{    
    typedef decltype(MakeTuple(std::declval<GetTime>())) Tuple0;
    Tuple0 t0;
    
    typedef decltype(MakeTuple(std::declval<SetTime>())) Tuple1;
    Tuple1 t1(1);
    
    typedef decltype(MakeTuple(std::declval<Sum>())) Tuple2;
    Tuple2 t2(1, 2);    
    
    typedef decltype(MakeTuple(std::declval<Distance>())) Tuple4;
    Tuple4 t4(1, 2, 3, 4);
}