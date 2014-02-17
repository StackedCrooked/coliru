// vector::push_back
#include <iostream>
#include <vector>
using namespace std;

int main (){
    int myint;
    vector<int> v1{1, 2, 3, 4, 5, 6, 7, 8};
    vector<int> v2{1, 2, 3, 4, 5};
    const size_t s1{v1.size()};
    const size_t s2{v2.size()};
    if(s1 > s1){
        myint = s1 - s2;
        for(int idk = 0; idk < myint; idk++)
            v1.push_back(myint);
    }
    else {
        myint = s1 - s2;
        for(int idk = 0; idk < myint; idk++)
            v2.push_back(myint); 
    } 
    cout << "V1 equals " << v1.size() << "\nV2 Equals " << v2.size() << "\nmyint equals  " << myint << endl;
    //const size_t sz{v1.size};
    /* vector<int> datsumdoe(sz);
    for(size_t idy = 0; idy < sz; ++idy){
        datsumdoe[idy] = v1[idy] + v2[idy];
        cout << datsumdoe[idy] << endl;} */
}