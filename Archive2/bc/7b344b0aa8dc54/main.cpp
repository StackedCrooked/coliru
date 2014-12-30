#include <algorithm>
#include <tuple>
#include <vector>
#include <iostream>

struct Data
{
    int A, B, C;    
};

bool DecreasingA(const Data & a, const Data & b) {
    return a.A > b.A;  // > instead of >=
}

bool DecreasingB(const Data & a, const Data & b) {
    if (a.B == b.B)   // both equal, so a does not precede b
        return false;
    if (b.B)          // b.B is true and a.B is false, so a does not precede b
        return false; 
    return true;      // a.B is true and b.B is false, so a does precede b
}

bool DecreasingBThenA(const Data & a, const Data & b) 
{
    return std::tie(a.B, a.A) > std::tie(b.B, b.A);
}

int main()
{    
    auto myVector = std::vector<Data> 
    {{ 1, 0, 5}, {1, 1, 8}, {2, 0, 2}, {0, 1, 3}};
    
    std::stable_sort(myVector.begin(), myVector.end(), DecreasingA);
    std::stable_sort(myVector.begin(), myVector.end(), DecreasingB);
    //std::stable_sort(myVector.begin(), myVector.end(), DecreasingBThenA);
    
    for (auto&& t : myVector)
        std::cout << "{" << t.A << ", " << t.B << ", " << t.C << "}\n";
}
