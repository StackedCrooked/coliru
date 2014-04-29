#include <vector>
#include <iostream>
#include <cassert>

const unsigned int N = 10;
    
void foo(const bool use_runtime_input, const unsigned int runtime_input = 0)
{
    assert(runtime_input < N);
    
    std::vector<unsigned int> indexes;
    indexes.reserve(N);
    
    if (use_runtime_input)
        indexes.push_back(runtime_input);
    
    for (unsigned int i = 0; i < N; i++) {
        if (use_runtime_input && i == runtime_input)
            continue;
        
        indexes.push_back(i);
    }
    
    std::vector<unsigned int>::const_iterator it = indexes.begin(), end = indexes.end();
    for ( ; it != end; ++it) {
        std::cout << *it << ' ';
    }
    
    std::cout << '\n';
}

int main()
{
    foo(false);
    foo(true);
    foo(true, 4);
    foo(true, 9);
}