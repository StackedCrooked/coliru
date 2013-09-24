#include <iostream>
#include <vector>
#include <future>


int main()
{
    std::vector<std::future<char>> vector;
    vector.push_back(std::async([](){return 'h';}));
    vector.push_back(std::async([](){return 'e';}));
    vector.push_back(std::async([](){return 'l';}));
    vector.push_back(std::async([](){return 'l';}));
    vector.push_back(std::async([](){return 'o';}));
    vector.push_back(std::async([](){return ' ';}));
    vector.push_back(std::async([](){return 'w';}));  
    vector.push_back(std::async([](){return 'o';}));
    vector.push_back(std::async([](){return 'r';}));
    vector.push_back(std::async([](){return 'l';}));
    vector.push_back(std::async([](){return 'd';}));
    
    for(auto& f : vector)
    {
        std::cout << f.get();
    }
        
    return 0;
}