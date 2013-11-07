#include <map>
#include <iostream>
#include <vector>


struct tp {
    int* pi;
    float* pf;
};


int main() {
    std::vector<tp> v;
    
    int* iptr = nullptr;
    //tp x(iptr, nullptr);  // Won't work
    //v.emplace_back(iptr, nullptr); // Won't work again
    v.insert(v.end(), {iptr, nullptr});
}