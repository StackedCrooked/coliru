#include <iostream>
using namespace std;

int main()
{
    int a[3] = {2,4,6};
    int *p = a;
    p[1] = 5;
    cout << a[1] << endl;
    p++;
    cout << *p << endl;
    
    cout << endl << "a: " << endl;
    for (int i = 0; i < 3; i++) {
        cout << a[i] << endl;
    }
    
    cout << endl << "p: " << endl;
    for (int i = 0; i < 3; i++) {
        cout << p[i] << endl;
    }
}
