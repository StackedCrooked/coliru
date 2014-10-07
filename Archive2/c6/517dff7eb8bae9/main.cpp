#include <iostream>
#include <cstddef>

using namespace std;

int main()
{
    std::cout << alignof(max_align_t) << '\n';
}