#include <iostream>
#include <string>

using namespace std;

int main() {
    string testStr = "TEST string";
    if (testStr.find("TEST") != string::npos) {
        std::cout << "Not npos\n";
    }
    if (testStr.find("TEST") == 0) {
        std::cout << "Position 0";
    }   
}