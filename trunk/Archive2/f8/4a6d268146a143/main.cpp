#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class F, class... Args>
void for_each_argument(F f, Args&&... args) 
{
    [](...){}((f(std::forward<Args>(args)), 0)...);  // ,0 used when lambda return is void, returning void is a valid expression so the ',' passes 0 to the lambda parameter instead of void.
}

template <class F, class... Args>
void for_each_argument_mine(F f, Args&&... args) 
{
    [](...){}((f(std::forward<Args>(args)))...);  // not needed if you guarantee your lambda returns are non-void.
}

int main()
{
    auto lam_mine = [](char a) -> int { cout << a; return 0; };
    for_each_argument_mine(lam_mine, 'H','e','l','l','o');
    
    auto lam = [](char a) { cout << a; };
    for_each_argument(lam, 'H','e','l','l','o');
}
