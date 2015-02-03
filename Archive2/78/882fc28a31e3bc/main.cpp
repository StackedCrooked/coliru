#include <fstream>
#include <string>
#include <iostream>
using namespace std;

int main() {
    ifstream foo("foo.txt");

    while (foo.good()){
        string bar;
        getline(foo, bar);
        cout << bar << endl;
    }
    cout << "^^^^^ Or maybe two? ^^^^^";
}