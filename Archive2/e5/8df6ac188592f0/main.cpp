#include <iostream>
using namespace std;
bool f(int t){
    int foo[2][2] = { {1,2}, {3,4} };
    
    if ( sizeof foo != 4 * sizeof(int) )
        throw 1;
        
    
    int *p = &foo[0][0];
    for(int i = 0; i <= 2; i++,p++){
        //if(*p == t) return true;            // g++: f(100) = false
        if ( foo[0][i] == t ) return true;    // g++: f(100) = true
    }
    return false;
}

int main(){
    int i;
    cin >> i;
    cout << boolalpha << "f(" << i << ") = "  << f(i) << endl;
    cin >> i;
    cout << boolalpha << "f(" << i << ") = "  << f(i) << endl;
    cin >> i;
    cout << boolalpha << "f(" << i << ") = " << f(i) << endl;
}
    