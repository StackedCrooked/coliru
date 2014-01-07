#include <algorithm>
#include <iostream>
#include <stdio.h>
using namespace std;

string FirstReverse(string str) { 
   std::reverse(str.begin(), str.end());
  // code goes here   
  return str; 
            
}

int main() { 
  
  // keep this function call here
  std::string input;
  cin >> input;
  cout << FirstReverse(input);
  return 0;
    
}