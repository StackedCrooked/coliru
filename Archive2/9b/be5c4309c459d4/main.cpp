#include <iostream>
#include <utility>
 
struct Bad
{
    Bad() {}
    Bad(Bad&&)  // may throw
    {
        std::cout << "Throwing move constructor called\n";
    }
    Bad(const Bad&) // may throw as well
    {
        std::cout << "Throwing copy constructor called\n";
    }
};
 
struct Good
{
    Good() {}
    Good(Good&&) noexcept // will NOT throw
    {
        std::cout << "Non-throwing move constructor called\n";
    }
    Good(const Good&) noexcept // will NOT throw
    {
        std::cout << "Non-throwing copy constructor called\n";
    }
};
 
int main()
{
    Good g;
    Bad b;
    Good g2 = std::move_if_noexcept(g);
    Bad b2 = std::move_if_noexcept(b);
}