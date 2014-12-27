#include <iostream>
#include <chrono>
#include <thread>
#include <vector>
#include <tuple>

template<typename... a>
void f(a......);

auto xxx(bool a)
{
    if (a)
        return "asasas\n";
    else
        return "qqqqqq\n";
}


int main()
{
    //std::vector<int> v;
    for (auto i : {1.1,3.1,4.0,5.1}){
        std::cout << i << ' ';
    }
    std::cout << '\n';
    
    std::cout << xxx(true);
    
    auto bar = std::make_tuple ("test", 3.1, 14, 'y');
    
    std::get<1>(bar) = 10.1; 
    
    std::cout << std::get<3>(bar);
    
    return 0;
}



