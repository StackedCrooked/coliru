#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct ca {
    int x;
    int y;
};
int main(){
    
    int x[]={0,1,2,3};
    int * i = &x[3];
    
    
    cout << i[-3] << endl;
    
    vector<ca> xx;
    xx.push_back(((ca){10,20}));
    cout << xx[0].x << endl;
    
    
    cout << "----------" << endl;
    
    typedef const int T;
    typedef T& TR;
    TR& v = 1;
    
}
