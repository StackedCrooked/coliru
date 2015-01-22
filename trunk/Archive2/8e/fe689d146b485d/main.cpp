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


// I got the below 2 methods from SO. A bit Lousy version :-)


template<typename Func, typename T>
T MinMax(Func&& f, T&& t)
{
    return std::forward<T>(t);
}


template<typename Func, typename First, typename Second, typename ...Rest>
auto MinMax(Func&& f, First&& first, Second&& second, Rest&& ...args) 
{
    return f(first, second) == first ? MinMax(std::forward<Func>(f), std::forward<First>(first), std::forward<Rest>(args)...)
                            : MinMax(std::forward<Func>(f), std::forward<First>(second), std::forward<Rest>(args)...);
}




int main(int argc, char* argv[])
{
  
    
    int minimum = MinMax_Jagan([] (auto x, auto y) { return x < y ? x : y; }, 1, 1.5, 2, 3, 4.5) ;
    double maximum = MinMax_Jagan([] (auto x, auto y) { return x > y ? x : y; }, 1, 2, 4.5, 3.5) ;
    
    std::cout << minimum << "\n";
    std::cout << maximum << "\n";
}
