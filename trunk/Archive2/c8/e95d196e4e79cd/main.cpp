// Tripcode@Home Rules!
//
// Just a trivial example of vector addition, chiefly just
//  to demonstrate passing work around using Coliru.
//
// Author: LLD!5DeRpYLOvE

#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

void add_vecs() 
{  
    vector<int> va{1, 2, 3, 4, 5};
    vector<int> vb{6, 7, 8, 9, 10};
    vector<int> vc(5);
    
    for (size_t idx{0}; idx < va.size(); ++idx)
        vc[idx] = va[idx] + vb[idx];
            
    cout << vc << endl;
}

int main()
{
    add_vecs();
}
