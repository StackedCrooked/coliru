#include <iostream>
using namespace std;

int main(){
    int i = 1;

    int c = 0;
    do{
        c++;
        i += i;
        cout << i << endl;
    }while (i > 0);

    cout << c << endl;
    return 0;
}