#include <iostream>
#include <string>
#include <vector>

struct type1 {
    int getVal() {
        return int();
    }
    typedef int subtype;
};
struct type2 {
    float getVal() {
        return float();
    }
    typedef float subtype;
};

template<class T> 
std::vector<typename T::subtype> something(T input) {
    return {input.getVal(),input.getVal()};
}

int main()
{
    something(type1{});
}
