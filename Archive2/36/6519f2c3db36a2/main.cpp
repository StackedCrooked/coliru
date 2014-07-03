#include <iostream>
#include <sstream>

using namespace std;

int main() {
    int tmp_available;
    int bought = 10;
    string available = 50;

    tmp_available=stoi(available); 
    tmp_available -= bought;

    stringstream tmp;
    tmp << tmp_available;
    available = tmp.str();
    
    cout << available;
}