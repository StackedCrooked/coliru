// vector::push_back
#include <iostream>
#include <vector>
using namespace std;

int main (){
    int myint = 1;
    cout << myint;
    vector<int> v1{1, 2, 3, 4, 5, 1, 0};
    vector<int> v2{5, 4, 3, 2, 1};
    vector<int> vBig{0};
    //if(v1.size() > v2.size())
        //vector<int> vBig = v1.size() - v2.size();
    const size_t sz{vBig.size()};
    //ya, ya, I know, I was determining the size based only on v1, which meant I could change
    //the length of v2 and it would not even recognize it. oh well~
    //I just don't really know who ask for v1&&v1 or eh, v1||v2 even.
    vector<int> datsumdoe(sz);
    for(size_t idy = 0; idy < sz; ++idy){
        datsumdoe[idy] = v1[idy] + v2[idy];
        cout << datsumdoe[idy] << endl;}
}