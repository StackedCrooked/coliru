#include <iostream>
#include <vector>

template<typename T>
class test
{
public:
    bool operator==(const test& rhs) const { return true; }
};


int main()
{
    test<int> a, b;
    if (a == b)
        std::cout << "yolo" << std::endl;
}