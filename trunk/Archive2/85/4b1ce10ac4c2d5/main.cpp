#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main() {

string input = "";

cout << "What's your name?:\n>";
 getline(cin, input);
 if(input = "Micaela"){
    cout << "You're the best" << input << endl << endl;
}
 else
    cout << "You kinda suck" << input << endl << endl;
return 0;
}