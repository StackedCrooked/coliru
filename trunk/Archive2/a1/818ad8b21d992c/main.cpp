#include <fstream>
#include <string>
#include <iostream>
using namespace std;

int main() {
    ifstream foo("foo.txt");

    string bar;
    while (getline(foo, bar)){
        cout << bar << endl;
    }
    cout << "^^^^^ Nothing extra. ^^^^^";
}