#include <algorithm>
#include <tuple>
#include <vector>
#include <iostream>

struct Data
{
    int A, B, C;    
};

bool DecreasingBThenA(const Data & a, const Data & b) 
{
    return std::tie(a.B, a.A) > std::tie(b.B, b.A);
}

int main()
{    
    auto myVector = std::vector<Data> 
    {{ 1, 0, 5}, {1, 1, 8}, {2, 0, 2}, {0, 1, 3}};
    
    std::stable_sort(myVector.begin(), myVector.end(), [](const Data & a, const Data & b){ return std::tie(a.B, a.A) > std::tie(b.B, b.A);} );
    
    for (auto&& t : myVector)
        std::cout << "{" << t.A << ", " << t.B << ", " << t.C << "}\n";
}
