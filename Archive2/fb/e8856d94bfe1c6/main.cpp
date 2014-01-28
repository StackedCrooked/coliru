#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main()
{
  int math;
  int a1;
  int a2 = 0;
  int a3 = 1;
  int answer;
  int amount = 0;
  int achecker = 1;

  cout << "Welcome to my calculator! Type '1' to add, type '2' to subtract, type '3' to multiply, type '4' to divide, and type '5' to exit." << endl;
  cin >> math;

  while(math = 1){
  cout << "Input how many numbers you wish to add:" << endl;
  cin >> amount;
  achecker = amount;
  do{
  cout << "Input the number you wish to add:" << endl;
  cin >> a1;
  answer = a1 + a2;
  a2 = a1;
  achecker = achecker - achecker + 1;
  }while(achecker < amount);
  cout << answer;
  }