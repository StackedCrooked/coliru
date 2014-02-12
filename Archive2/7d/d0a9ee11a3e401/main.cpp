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

// give the vector<> class an output stream operator '<<' for simple content output
template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& elem : vec)
        os << elem << ' ';

    return os;
}

// initialize and add two independant vectors into a third and print that one out
void add_print_vecs() 
{  
    vector<int> va{1, 2, 3, 4, 5};
    vector<int> vb{6, 7, 8, 9, 10};
    vector<int> vc(5);
    
    for (size_t idx{0}; idx < va.size(); ++idx)
        vc[idx] = va[idx] + vb[idx];
            
    cout << vc << endl;
}

// the entry point for all C++ apps
int main()
{
    add_print_vecs();
}
