// Tripcode@Home Rules!
//
// Just a trivial example of vector addition, chiefly just
//  to demonstrate passing work around using Coliru.
// TODO: Edit this example's vector values,
//  then pass that in turn onto someone else.
//
// Author: LLD!5DeRpYLOvE

#include <iostream>
#include <vector>

using std::vector;
using std::cout;
using std::endl;

// give the vector<> class an output stream operator '<<' for simple content outputting
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
    
    const size_t sz{va.size()};
    vector<int> vout(sz);
    
    for (size_t idx{0}; idx < sz; ++idx)
        vout[idx] = va[idx] + vb[idx];
            
    cout << vout << endl;  // here's where we use the vector's new '<<' operator created above.
}

// the entry point for all C++ apps
int main()
{
    add_print_vecs();
}
