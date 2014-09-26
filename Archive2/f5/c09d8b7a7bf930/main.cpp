#include <string>
#include <iostream>
using namespace std;

int main() {
string input;
getline(cin, input);

char sep = ' ';
string readArray[10];

// Splits the inputted line into separate strings depending on delimiter (' ')
for (size_t p = 0, q = 0, i = 0; p != input.npos && i<readArray.size(); p = q, i++){
    string result;
    result = input.substr(p + (p != 0), (q = input.find(sep, p + 1)) - p - (p != 0)) << endl;
    readArray[i] = result;
}
}
