// Ensure two vector<int>s are equivalent sizes first, then add them together.
// Author: LLD!5DeRpYLOvE
// Respin of: http://coliru.stacked-crooked.com/a/34542cba6c40b27b
#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
    int sizediff{-1};

    // Initialize a pair of different length vectors.
    vector<int> v1{21, 31, 41, 51, 9};
    vector<int> v2{8, 7, 6, 5, 4, 3, 2, 1};
    const size_t s1{v1.size()};
    const size_t s2{v2.size()};
    
    cout << "Original sizes:\n V1 equals " << s1 << "\n V2 Equals " << s2 << endl;    
    
    // First case: v1 is bigger.
    if(s1 > s2) {
        sizediff = s1 - s2;
        while (sizediff--) // while() ends once sizediff == 0
            v2.push_back(0); 
    }
    // Second case: v2 is bigger.    
    else 
    if(s2 > s1) {
        sizediff = s2 - s1;
        while (sizediff--) // while() ends once sizediff == 0
            v1.push_back(0); 
    } 
    // Third case: equivalent sizes.
    else
        sizediff = 0;
    
    cout << "New sizes:\n V1 equals " << v1.size() 
         << "\n V2 Equals " << v2.size() 
         << "\n sizediff equals " << sizediff << endl;
    
    // Now add the vectors and print the results.
    const size_t sz{v1.size()};
    vector<int> datsumdoe(sz); 
    for(size_t idy{0}; idy < sz; ++idy) {
        datsumdoe[idy] = v1[idy] + v2[idy];
        cout << datsumdoe[idy] << endl;
    } 
}