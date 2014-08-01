#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

/* this version of change works fine for me when i store the
   incoming value into a static variable.
int change(int n){
    static int m=n; //with this uncommented i get the right behavior
    return m * m;
}*/

int change(int n){
    return n*n;
}

int main(){
    vector<int> v2(3,3), v1;

    v2.reserve(v2.size() * 2);
    transform(v2.begin(),v2.end(),back_inserter(v2),change);

    for(auto v: v2)
    { 
        cout << v <<"  ";  // prints out a strange random 5th value in v2.
    }    

    return 0; 
}
