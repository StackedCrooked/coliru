#include <iostream>
#include <bitset>
int main()
{
    std::bitset<4> mask("1100");
    std::bitset<4> val("0111");
    val xor_eq mask;
    std::cout << val << '\n';
    std::cout << "hello" <<'\n';
}