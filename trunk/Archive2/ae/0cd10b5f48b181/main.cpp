#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct S {
    S(const char *) {}
    operator bool() const {return true;}
};

int main() {

S input = "";

//cout << "What's your name?:\n>";
// getline(cin, input);
 if(input = "Micaela"){
//    cout << "You're the best" << input << endl << endl;
}
 else {}
//    cout << "You kinda suck" << input << endl << endl;
return 0;
}