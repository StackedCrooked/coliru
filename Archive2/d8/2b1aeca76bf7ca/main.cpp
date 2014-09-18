#include <iostream>

using namespace std;


int main(int argc, char *argv[]) {

    int x = 42;
    cout << "x=" << (x ? std::to_string(x) : "???") << "!\n";
    
    cout << "x="; 
    (x ? cout << x : cout << "???") << "!";
}