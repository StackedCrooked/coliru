#include <iostream>
#include <climits>

inline int32_t max(int32_t a, int32_t b)
{ 
    return a - ((a-b) & (a-b)>>31);
}

int main() {
    std::cout << max(-2, INT_MAX) << std::endl;
}
