#include <vector>
#include <iostream>


int main()
{
    std::vector<int> vec = { 1, 2, 3 };
    
    for (auto&& n : [&]{ decltype(vec) tmp; std::swap(vec, tmp); return tmp; }()) // "consume" 
    {
        std::cout << n;
    }
    
    std::cout << '\n' << vec.size() << std::endl;
}
