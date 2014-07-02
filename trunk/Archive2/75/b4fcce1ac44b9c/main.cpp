#include <iostream>
using namespace std;
bool f(int t){
    struct
    {
        int a[2];
        int b[2];
    } foo = {{1, 2}, {3, 4}};
    
    if ( sizeof foo != 4 * sizeof(int) )
        throw 1;
        
    int *p = &foo.a[0];
    for(int i = 0; i <= 2; i++,p++){
        if(*p == t) return true;
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
    