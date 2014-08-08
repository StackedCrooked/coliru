
#include <climits>
#include <iostream>

int main () {
    int y = INT_MAX;
    std::cout <<  (y - (y * 0.5) == y/2);
}