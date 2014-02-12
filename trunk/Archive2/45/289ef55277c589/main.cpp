#include <iostream>
#include <string>
#include <ifstream>

using namespace std;

int main() {
    string filename;
    cout << "Enter the filename: ";
    cin >> filename;
    ifstream myfile(filename);

    //code that does stuff, eg:
    while (myfile >> thing) {
        mydata[i] = thing;
        i = i + 1; //etc, this *isn't* an issue
    }
}