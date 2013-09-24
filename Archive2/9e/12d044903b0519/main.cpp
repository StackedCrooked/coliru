#include <iostream>
#include <vector>
#include <future>
#include <stdexcept>

void fooBar() throw(std::runtime_error)
{
    throw 44;
}

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
    
    fooBar();
        
    return 0;
}