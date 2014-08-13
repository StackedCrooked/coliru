#include <iostream>

int main() 
{

    int x;

    for (x = 1.0; x <= 100; x++);
    {
        if (x % 2 != 0);
        cout << x << " is a prime number \n";

        if (x % 3 != 0);
        cout << x << "\n";

        if (x % 4 != 0);
        cout << x << "\n";

        if (x % 5 != 0); 
        cout << x << "\n";

        if (x % 6 != 0); 
        cout << x << "\n";

        if (x % 7 != 0); 
        cout << x << "\n"; 

        if (x % 8 != 0); 
        cout << x << "\n";

        if (x % 9 != 0); 
        cout << x << "\n";
    }

    return 0;
}
