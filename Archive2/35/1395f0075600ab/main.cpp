#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
 
int main()
{
    int i = 10;
    std::function<int(int)> func2 = [&](int x) { return x+i; };
    std::function<int(int)> func3 = [&](int x) { int i = 20; return x+i; };

    std::cout << "func2: " << func2(6) << '\n'; 
    std::cout << "func3: " << func3(6) << '\n'; 

}
