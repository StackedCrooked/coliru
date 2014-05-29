
template<class Left, class Right>
bool is_any_of(const Left& left, const Right& right) 
{return left==right;}

template<class Left, class Right, class...Rest>
bool is_any_of(const Left& left, const Right& right, const Rest&...rest) 
{return left==right || is_any_of(left, rest...);}

#include <iostream>
int main() {
    int three = 4;
    std::cout << is_any_of(three, 1, 2, 3, 4);
}