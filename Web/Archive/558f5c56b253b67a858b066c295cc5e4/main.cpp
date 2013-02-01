#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

std::vector<int> getVector()
{
    std::vector<int> v = {20, 30, 40};
    
    return v;
}

int main()
{
    std::cout << "Hello GCC " << __VERSION__ << "!" << std::endl;
    
    auto v = getVector();
    
    std::for_each(v.begin(), v.end(), [](int value){ std:: cout << "==> " << value << std::endl;});
    
    std::thread t([](){ std::cout << "Hello Thread!"; });
    t.join();
    
    std::cout << "Finish\n";
}