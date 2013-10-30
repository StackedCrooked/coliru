#include <sstream>
#include <iostream>
#include <string>
using namespace std;
 
int main() {
    cout << (stringstream() << "Liczba " << 42).str();
}