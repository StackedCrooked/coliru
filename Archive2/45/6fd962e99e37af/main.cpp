#include <algorithm>
#include <vector>
#include <iostream>
#include <cassert>

template <typename T, size_t N>
size_t len(T (&)[N])
{
   return N;
}

int main()
{
    int array[] = {16,9,10,19,2};
    
    const int START = 1;  // user input (1-based index)
    const int END   = 3;  // user input (1-based index)
    
    assert((START-1) >= 0 && (START <= len(array)));
    assert((END-1) >= 0   && (END <= len(array)));
    
    std::vector<int> v(array+(START-1), array+END);
    std::sort(std::begin(v), std::end(v));
    
    for (auto elm : v) {
       std::cout << elm << ' ';
    }

}