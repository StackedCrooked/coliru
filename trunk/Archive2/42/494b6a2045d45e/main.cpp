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

// initialize and add two separate vectors into a third vector, then print that one out
void add_print_vecs() 
{  
    // initialize
    vector<int> va{60, 50, 30, 10, 34};
    vector<int> vb{9, 19, 39, 59, 35};
    const size_t sz{va.size()};
    
    // delcare only
    vector<int> vsum(sz);
    
    // add
    for (size_t idx{0}; idx < sz; ++idx)
        vsum[idx] = va[idx] + vb[idx];

    // print out sums
    cout << vsum << endl;  // here's where we use the vector's handy new '<<' operator defined above.
}

// the entry point for all C++ apps
int main()
{
    add_print_vecs();
}
