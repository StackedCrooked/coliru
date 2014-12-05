#include <iostream>
#include <vector>

class aHistogram : public std::vector<int>
{
public:
    aHistogram() : vector<int>(10) {}
    void clear() { vector<int>::clear(); }
};

int main()
{
    aHistogram a;
    std::cout << a.size() << '\n';
    a.clear();
    std::cout << a.size() << '\n';
}
