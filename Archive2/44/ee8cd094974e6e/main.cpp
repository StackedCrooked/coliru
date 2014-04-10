#include <iostream>
#include <string>
#include <vector>
#include <stack>


constexpr unsigned int N = 100;

int main() {
    double a[N][N] = {0};
    
    /* Pointer */
    double (*a_ptr)[N] = a;
    
    
    /* Specified Reference Type */
    double (&a_ref)[N][N] = a;
    
    /* C++11 Auto Reference */
    auto &a_autoref = a;
}

