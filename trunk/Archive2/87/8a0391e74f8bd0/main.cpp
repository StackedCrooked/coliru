#include <iostream>
template<typename ...Args>
void printer(Args&&... args) {
    (std::cout << ... << args) << '\n';
}
int main()
{
    printer(1, 2, 3, "abc");
}