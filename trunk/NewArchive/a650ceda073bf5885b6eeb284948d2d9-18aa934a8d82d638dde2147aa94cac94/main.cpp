#include <vector>
#include <iostream>
#include <cstdarg>

//Don't do this. Use templates instead. Please.
std::vector<int> make_vector(int num, ...) {
    std::vector<int> result;
    va_list args;
    va_start(args,num);
    for(int i = num; i >= 0; i = va_arg(args,int))
        result.push_back(i);
    va_end(args);
    return result;
}

int main() {
    auto it = make_vector(1,5,6,7,-1); //-1 to end the loop..
    for(auto& i : it)
        std::cout << i << ' ';
}