#include <iostream>

struct YourMomIsFat
{
    operator bool() const { std::cout << "Yeah, she's pretty fat." << std::endl; return true; }
};

struct YourMomIsThin
{
    operator bool() const { std::cout << "Yeah, ...right." << std::endl; return false; }
};

int main()
{
    std::cout << YourMomIsFat() && YourMomIsThin();
}