#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
  // your code goes here
  string x = "a";
  cout << "x starts: " << (void*)&x[0] << endl;
  string m = std::move(x);
  cout << "move: x starts: " << (void*)&m[0] <<endl;

  return 1;
}
