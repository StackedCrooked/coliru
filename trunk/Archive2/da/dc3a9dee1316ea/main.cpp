#include <iostream>
#include <algorithm>
#include <type_traits>

// The other day I read about MinMax(..) eg. in python where you can pass any number of arguments to a function
// and then calculate the result we want.


// Better version.
template<typename ...Args>
struct TypeOfArgs
{
    typedef typename std::common_type<Args...>::type type;
};

template<typename Func, typename First>
typename std::common_type<First>::type MinMax_Jagan(Func&& f, First&& first)
{    
    return first; 
}

template<typename Func, typename First, typename Second>
typename std::common_type<First, Second>::type MinMax_Jagan(Func&& f, First&& first, Second&& second)
{    
    return f(std::forward<First>(first), std::forward<Second>(second));
}


template<typename Func, typename First, typename Second, typename ...Args>
typename TypeOfArgs<First, Second, Args...>::type MinMax_Jagan(Func&& f, First&& first, Second&& second, Args&& ...args)
{    
    return MinMax_Jagan(std::forward<Func>(f), f(first, second), std::forward<Args>(args)...);
}


int main(int argc, char* argv[])
{ 
    
    auto minimum = MinMax_Jagan([] (auto x, auto y) { return x < y ? x : y; }, 1.5,10,3,6.7,8) ;
    auto maximum = MinMax_Jagan([] (auto x, auto y) { return x > y ? x : y; }, 1,10,3,6.7,8) ;
    
    std::cout << minimum << "\n";
    std::cout << maximum << "\n";
}
