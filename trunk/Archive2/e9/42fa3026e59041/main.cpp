#include <iostream>
#include <sstream>
#include <string>

int main() {
using namespace std;
istringstream i { "something;123D;;LINE TABULATION;\nsomething;123D;;LINE TABULATION;\nsomething;123D;;LINE TABULATION;\n" };
string a, b, c, d, newline;
while( getline(i, a, ';') && getline(i, b, ';') && getline(i, c, ';') && getline (i, d, ';') && getline(i, newline) )
  cout << d << ',' << c << '-' << b << ':' << a << endl; 
}
