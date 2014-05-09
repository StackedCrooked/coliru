#include <iostream>
 
unsigned int naive_ackermann(unsigned int m, unsigned int n) {
    if (m == 0)
        return n + 1;
    else if (n == 0)
        return naive_ackermann(m - 1, 1);
    else
        return naive_ackermann(m - 1, naive_ackermann(m, n - 1));
}

int main()
{
    std::cout << naive_ackermann(2,4) << std::endl;
}