#include <iostream>
using namespace std;
int main(){
    int *u;
    {
        int y = 7;
        u = &y;
    }
    {
        int x = 42;
        cout << &x << endl;
    }
    cout << *u << endl;
}