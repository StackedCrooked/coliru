#include <algorithm>
#include <cassert>

#define max(a,b) (a > b ? a : b)

int main() {
    int a = 5, b = 3;
    
//    int res = max(a, b = 6);
    int res = (std::max)(a, b = 6);
    
    assert(res == 6);
}