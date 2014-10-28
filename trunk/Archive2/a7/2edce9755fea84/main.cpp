#include <iostream>
#include <type_traits>

constexpr int test(int x) {
    int y = 2*x; // C++17/1y adds "relaxed constexpr", allows (non const/constexpr!) variables...
    ++y;
    
    if (y > 5) y = -1; // ...if statements...
    
    for (int i = 0; i < x; ++i) { // ...and loops! (with constexpr bounds)
        y = i;
    }
    
    return y;
}

int main()
{
    using my_constant = std::integral_constant<int, test(3)>;

    std::cout << "result: " << my_constant::value << "\n";
}
