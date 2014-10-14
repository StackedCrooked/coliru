#include <iostream>
#include <string>
#include <vector>

struct type1 {
    int getVal() {
        return int();
    }
};
struct type2 {
    float getVal() {
        return float();
    }
};

template<class T> 
auto something(T input) -> std::vector<decltype(input.getVal())>  {
    return {input.getVal(),input.getVal()};
}

int main()
{
    something(type1{});
    something(type2{});
}
