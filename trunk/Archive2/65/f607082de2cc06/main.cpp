#include <regex>
#include <iostream>
using namespace std;

//...
int main () {
if (!regex_match("abab",regex("(ab?)*")))
{
    cout << "lel";
  //the problem is - why we are here? why it doesn't match?
}
cout << "lol";
}