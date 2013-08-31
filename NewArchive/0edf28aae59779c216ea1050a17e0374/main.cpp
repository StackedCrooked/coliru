#include <iostream>
#include <vector>
#include <functional>


#define ASSERT_TWO(a, b)  { constexpr int x = 1 / (reinterpret_cast<std::ptrdiff_t>(a) - reinterpret_cast<std::ptrdiff_t>(b)) }

int *global;

int main()
{
    int *local;
    
    ASSERT_TWO(global, global);
    ASSERT_TWO(local, local);
}