#include <vector>
#include <iostream>

struct T
{
    T() { std::cout << "def-cons\n"; }
    ~T() { std::cout << "dest\n"; }
    T(const T&) = delete;
};

int main()
{
    std::vector<T> v(5);
}
