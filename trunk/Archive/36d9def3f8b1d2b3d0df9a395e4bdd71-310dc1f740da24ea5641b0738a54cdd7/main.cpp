#include <string>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    string secondArg = string(argv[2]);

    if ("-k" == secondArg) {
        cout << "they compare equal" << endl;
    } else {
        cout << "they don't compare equal" << endl;
    }
    cout << secondArg << "ad" << endl;
    cout << "-kad" << endl;
}