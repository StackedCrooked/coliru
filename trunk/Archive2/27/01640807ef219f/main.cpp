#include <iostream>

bool isDivideable (int a, int b) {
    bool can_div = false;
if (a%b == 0)
{
    can_div = true;
      std::cout << b << std::endl;
}
     return can_div;
}
bool isPremier(int n)
{
    bool Premier = true;
    if (n>3)
        {
            int i = 2;
            while ( (i < n/2 ) && (Premier == true)) {
            Premier = !isDivideable(n,i);
            i++;
            }
        }
    return Premier;
}



int main()
{
    std::cout << "100" <<  isPremier(1897) << std::endl;
}
