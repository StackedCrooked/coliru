#include <string>
#include <sstream>
#include <iostream>
using namespace std;

int main()
{
  string str = "this is a car\nand another\nand another";

  std::stringstream ss;
  ss << str;

  string a,b;
  ss >> a >> ws;
  getline(ss, b);  
  cout << a << "\n";
  cout << b << "\n";
}