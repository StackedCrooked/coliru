// vector::push_back
#include <iostream>
#include <vector>
using namespace std;

int main (){
    int myint = 0;
    vector<int> v1{1, 2, 3, 4, 5, 1, 0};
    vector<int> v2{5, 4, 3, 2, 1};
    const size_t s1{v1.size()};
    const size_t s2{v2.size()};
    if(s1 > s1)
        myint = s2 - s1;
    else 
        myint = s1 - s2;
    cout << myint << endl;
    /* const size_t sz{vBig};
    vector<int> datsumdoe(sz);
    for(size_t idy = 0; idy < sz; ++idy){
        datsumdoe[idy] = v1[idy] + v2[idy];
        cout << datsumdoe[idy] << endl;} */
}