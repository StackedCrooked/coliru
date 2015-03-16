#include <iostream>

//using namespace std;

// WITH this forward decleration the output is A=1 and B=2
// WITHOUT this forward decleration the output is A=2 and B=1
// WHY??
//void swap(int a, int b);

int main() {

    int a = 1;
    int b = 2;

    swap(a, b);

    cout << "A: " << a << endl;
    cout << "B: " << b << endl;

    system("PAUSE");

    return 0;
}

void swap(int a, int b) {
    int tmp = a;
    a = b;
    b = tmp;
}