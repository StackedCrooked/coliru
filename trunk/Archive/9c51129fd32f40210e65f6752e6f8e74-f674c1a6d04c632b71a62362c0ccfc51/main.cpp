#include <vector>
#include <iostream>
using namespace std;

int main() {

  vector<bool> vb = {false, true};    // std:: canonical proxy example
  cout << vb[0] << endl;
  auto b1 = vb.back();   
  b1 = true;
  cout << vb[0] << endl;
  
}

