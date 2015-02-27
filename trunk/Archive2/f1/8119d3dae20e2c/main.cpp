#include <iostream>

using namespace std;

int main()
{
 string var {"test"};
 string &lr {var};
 
 cout << __VERSION__ << '\n';

 cout << var << "\n";
 cout << lr << "\n";
}