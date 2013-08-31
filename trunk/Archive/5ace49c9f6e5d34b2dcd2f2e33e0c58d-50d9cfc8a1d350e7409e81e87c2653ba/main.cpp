#include <string>
#include <iostream>
#include <cmath>
using namespace std;

int main(){
  string input;
  char digit;
  int length;
  int result = 0;

  cout << "Enter a number in binary" << endl;
  cin >> input;
  cout << endl;

  length = input.length();

  for (int i = 0; i < length; i++)
  {
    digit = input[i];
    int aaa = (int) digit - '0'; // is that correct ? I think not.
    result = aaa * pow(2,i) + result;
  }
  cout <<result;
  return 0;
}