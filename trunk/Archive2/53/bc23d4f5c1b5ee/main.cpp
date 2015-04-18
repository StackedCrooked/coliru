#include <iostream>

    int sum(int u)
    {return u;}  // Recursion-End
 
    template<typename... Args>
    int sum(int u, Args... rest)
    {
        return u + sum(rest...);
    }
    
int main()
{
    std::cout << "5 + 7 + 1 + 3 - 2 = " << sum(5, 7, 1, 3, -2);

   return 0;
}