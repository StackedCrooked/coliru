#include <iostream>
#include <type_traits>

struct abc {
    int value;
    abc(std::true_type, int v)
        : value(v*2)
    {}
    abc(std::false_type, int v)
        : value(v)
    {}
    
    abc(bool b
};
    
int main() {
    
    return 0;
}