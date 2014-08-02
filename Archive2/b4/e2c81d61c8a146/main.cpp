#include <random>
#include <iostream>
#include <vector>
#include <string>
 
int main()
{
    std::vector<std::string> vec {"mot1", "mot2", "mot3", "mot4", "mot5", "mot6", "mot7", "mot8", "mot9"};
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, vec.size() - 1);
 
    for (int n=0; n<10; ++n)
    {
        std::cout << vec[dis(gen)] << ' ';
    }
    std::cout << '\n';
}