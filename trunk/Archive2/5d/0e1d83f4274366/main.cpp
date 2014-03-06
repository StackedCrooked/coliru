#include <iostream>

int main()
{
    for (int i = 0; i < 777; i++)
    {
        int a = i;
        a = a ^ ((255 ^ a) & -(255 < a)); // min(255, a)
        if (a != i)
        {
            std::cout << "a:" << i << " -> min(255, i):" << a << "\n";
            break;
        }
    }
}
