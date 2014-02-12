#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
    string filename;
    cout << "Enter the filename: ";
    cin >> filename;
    ifstream myfile(filename.c_str());
}