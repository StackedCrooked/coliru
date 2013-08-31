#include <iostream>
#include <string>
#include <vector>


template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}


int main()
{
    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    
    int i;
    std::cout << "Please enter an integer value: ";
    std::cin >> i;
    std::cout << "The value you entered is " << i;
    std::cout << " and its double is " << i*2 << ".\n";
        
    std::cout << words << std::endl;

}
