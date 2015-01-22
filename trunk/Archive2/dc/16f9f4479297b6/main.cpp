#include <iostream>
#include <algorithm>

// The other day I read about MinMax(..) eg. in python where you can pass any number of arguments to a function
// and then calculate the result we want.



template<typename T, typename ...Args>
struct TypeOfArgs
{
    typedef T type;
};


template<typename Func, typename ArgsType, size_t SZ>
ArgsType MinMaxHelper(Func&& f, const ArgsType(&entries)[SZ], ArgsType const& res, int index)
{
    if (index == SZ)
    {
        return res;
    }
    return MinMaxHelper(std::forward<Func>(f), entries, f(res, entries[index]), index+1);
}



template<typename Func, typename ...Args>
typename TypeOfArgs<Args...>::type MinMax_Jagan(Func&& f, Args&& ...args)
{
    typedef typename TypeOfArgs<Args...>::type ArgType;    
    ArgType entries[] = {std::forward<Args>(args)...};
    return MinMaxHelper(std::forward<Func>(f), entries, entries[0], 1);
}


// I got the below 2 methods from SO.


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
   int minimum = MinMax([] (auto x, auto y) { return x < y ? x : y; }, 1.5, 2); 
    int maximum = MinMax([] (auto x, auto y) { return x > y ? x : y; }, 1, 2, 3, 4.5); 

    std::cout << "min:" << minimum << "\nmax:" << maximum << "\n";
    
    
    
  //  std::cout << vmin(1,2,3,4);
}
