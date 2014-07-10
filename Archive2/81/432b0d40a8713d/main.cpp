P#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <set>

class foo
{
public:
    int data;

    template<class T>
    bool in(std::initializer_list<T> numbers) const
    {
        std::cout << "initializer_list overload: ";
        return std::find(begin(numbers), end(numbers), data) != end(numbers);
    }
    
    template<class T>
    bool in(std::set<T> const& numbers) const
    {
        std::cout << "set overload: ";
        return numbers.find(data) != end(numbers);    
    }
};

int main()
{
    foo f{1};
    std::cout << f.in({1, 2, 3}) << "\n";
    std::cout << f.in({2, 3, 4}) << "\n";
    
    std::cout << f.in(std::set<int>{ 1, 2, 3 }) << "\n";
    std::cout << f.in(std::set<int>{ 2, 3, 4 }) << "\n";
}
