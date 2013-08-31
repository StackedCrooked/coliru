#include <iostream>

using namespace std;


int main() {
    int empty1;
    int empty2;
    int contain1 = 100;
    int contain2 = 200;
    int container [2] = { contain1, contain2 };
    int* empty_container [2] = { &empty1, &empty2 };
    // ^ Notice this
    int i = 0;
    while ( i != 2 ) {
        *(empty_container[i]) = i;
    //  ^ Also this
        cout << endl << "empty_container[i]: " << empty_container[i] << endl
        << "empty1: " << empty1 << endl << "empty2: " << empty2 << endl;
        cout << "i: " << i << endl;
        cout << "container[i]: " << container[i] << endl;
        cout << "contain1: " << contain1 << endl;
        cout << "contain2: " << contain2 << endl;
        i++;
    }
}