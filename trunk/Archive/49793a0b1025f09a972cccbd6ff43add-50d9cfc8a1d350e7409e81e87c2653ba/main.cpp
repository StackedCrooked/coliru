#include <iostream>
#include <string>
#include <vector>
#include <thread>


using Sentence = std::vector<std::string>;


std::ostream& operator<<(std::ostream& os, const Sentence & sentence)
{
    for (const auto & word : sentence)
    {
        os << word << " ";
    }
    return os;
}

void f() { std::cout<<"Hello from thread!\n"; }

int main()
{
    std::thread t([] () {
    Sentence sentence = { "Hello", "from", "GCC", __VERSION__, "!" };    
    std::cout << sentence << std::endl;
    });
    
    t.join(); 
}
