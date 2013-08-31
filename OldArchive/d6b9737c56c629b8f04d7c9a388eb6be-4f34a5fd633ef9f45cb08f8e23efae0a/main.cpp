#include <iostream>
#include <string>
using namespace std;

void paramCheck (const string& s) { cout << ". Param is const ref.\n";}
void paramCheck (string& s) {cout << ". Param is non-const ref.\n";}
void paramCheck (const string&& s) { cout <<  ". Param is const rvalue-reference.\n";}
void paramCheck (string&& s) {cout << ". Param is non-const rvalue-reference.\n";}

const string func() {return "fsda";}
const string&& func(string&& in) {return std::move(in);}

int main() {
    paramCheck(func());
    paramCheck(func("fdasfdsagds"));
}