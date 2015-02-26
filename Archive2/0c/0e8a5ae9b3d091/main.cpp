#include <iostream>

using namespace std;

int main()
{
 string var {"test"};
 string &lr {var};

 cout << var << "\n";
 cout << lr << "\n";
}