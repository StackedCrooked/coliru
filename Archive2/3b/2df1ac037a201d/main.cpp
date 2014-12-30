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
    
    std::stable_sort(myVector.begin(), myVector.end(), [](const Data & a, const Data & b){ 
        return a.B == b.B ? 
            a.A == b.A ? 
                a.C < b.C 
                : a.A > b.A
            : a.B > b.B;
            
//        if (a.B == b.B)
//            if (a.A == b.A)
//                return a.C < b.C;
//            else
//                return a.A > b.A;
//        else
//            return a.B > b.B;
    });
    
    for (auto&& t : myVector)
        std::cout << "{" << t.A << ", " << t.B << ", " << t.C << "}\n";
}
