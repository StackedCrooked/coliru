#include <iostream>
using namespace std;
bool f(int t){
    struct
    {
        int a[2];
        int b[2];
    } foo = {{1, 2}, {3, 4}};
    for(int i = 0; i <= 2; i++){
        if(foo.a[i] == t) return true;
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
    