#include <iostream>
#include <array>
#include <algorithm>

int main()
{
 std::array<int, 3> pole{ { 1, 2, 3 } };

 for (auto x : pole)
 {
 std::cout << x << std::endl;
 }

 std::for_each(pole.begin(), pole.end(), [](int& x) { std::cout << x << std::endl; } );

 return 0;
}