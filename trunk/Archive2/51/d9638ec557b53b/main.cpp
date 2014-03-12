#include <iostream>
#include <vector>

template<class It, class UnaryOp1, class UnaryOp2>
void loop_and_a_half(It first, It last, UnaryOp1 op1, UnaryOp2 op2)
{
    while (true) {
        op1(*first++);
        if (first == last) break;
        op2(*first);
    }    
}

int main()
{
    auto somelist = std::vector<int>{1,2,3,4,5,6,6,7,8,9,6};
    
    loop_and_a_half(
        begin(somelist), end(somelist),
        [](auto e) { std::cout << e; },
        [](auto) { std::cout << ", "; }
    );
}