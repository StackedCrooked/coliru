#include <iostream>
using namespace std;
int main () {
    int N = -1;
    cout << " Input an integer:";
    if(!(cin >> N)) {
        cout << "Input a valid number!" << endl;
        cout << "N = " << N << endl;
    }
    else {
        cout << " The integer entered is:" << N << endl;
    }
    return 0;
}