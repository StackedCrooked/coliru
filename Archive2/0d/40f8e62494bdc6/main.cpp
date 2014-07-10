#include <algorithm>
#include <initializer_list>
#include <iostream>

class foo
{
public:
    int data;
};

template<class T>
bool foo_in_numbers(std::initializer_list<T> numbers, foo const& f)
{
    return std::find(begin(numbers), end(numbers), f.data) != end(numbers);
}

int main()
{
    foo f{1};
    std::cout << foo_in_numbers({1, 2, 3}, f) << "\n";
    std::cout << foo_in_numbers({2, 3, 4}, f) << "\n";
}
