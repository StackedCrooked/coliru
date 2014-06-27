#include <iostream>

int main() {
    using namespace std;

    const int x = 42;
    
    *const_cast<int*>(&x) = 24; // variable changed?
    
    cout << x << endl; // let's see...
}