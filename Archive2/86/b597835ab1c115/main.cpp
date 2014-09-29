#include <iostream>
using namespace std;
int main()
{
int int_var = 1500000000; //1,500,000,000
cout << "\nint_var = " << int_var;
int_var = (int_var * 10) / 10;
cout << "\nint_var2 = " << int_var; //wrong answer
cin >> int_var;
int_var = (static_cast <float>(int_var)* 10) ;
cout << "\nint_var3 = " << int_var; //1,500,000,000
cout << endl;
system("pause");
return 0;
}