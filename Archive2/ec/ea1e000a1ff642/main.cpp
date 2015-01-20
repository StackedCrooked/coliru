#include <iostream>
#include <fstream>
using namespace std;

int main() {
    int a;
    a=0;
    
    ifstream ievade;
    ievade.open ("fails.txt");
    ievade >> a;
    cout << a;
}