#include <iostream>
#include <string>
#include <vector>

#include <typeinfo>   // typeid
#include <algorithm>  // count_if & co.
#include <functional> // function

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    os << "vector<" << typeid(T).name() << ">[ ";
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    os << "]";
    return os;
}

int main()
{
    std::vector<int> numbers{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    std::cout << "Numbers: " << numbers << ".\n";
    
    std::function<bool (int)> isEven = [](int i) { return i % 2 == 0; };
    auto evenCount = std::count_if(numbers.begin(), numbers.end(), isEven);
    std::cout << "Vector contains " << evenCount << " even numbers.\n";
        
    std::vector<int> evenNumbers(evenCount);
    std::copy_if(numbers.begin(), numbers.end(), evenNumbers.begin(), isEven);
    std::cout << "Even numbers are: " << evenNumbers << ".\n";
    
    std::function<int (int)> quad = [] (int x) { return x*x; };
    std::vector<int> quads(numbers.size());
    std::transform(numbers.begin(), numbers.end(), quads.begin(), quad);
    std::cout << "Quads: " << quads << ".\n";
    
    
    return 0;
}
