#include <cmath>
#include <iostream>

class some {};

bool operator&(const some&, int) {
    return true;
}

int main() 
{
    some variable;
    std::cout << bool(variable & 0x08);
}