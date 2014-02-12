#include <iostream>

void r(int i, int s) 
{
    if (i<=11) {
        s+= i;
       r(i+1, s);
    }
    std::cout << s;
}

int main() {
    int s=0;
    r(0, s);
}