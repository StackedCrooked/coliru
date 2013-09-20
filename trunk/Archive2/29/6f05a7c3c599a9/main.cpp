#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int a;
    cout << "Enter a number for a: "; //Prompts the user for a and b inputs
    cin >> a;
    int b;
    cout << "Enter a number for b: ";
    cin >> b;
    cout << "A is "                           << a << "\tB is " << b << endl
         << "Sum of a and b is equal to "     << a << "+"       << b << "and the result is " << (a + b) << endl
         << "Product of a and b is equal to " << a << "*"       << b << "and the result is " << (a * b) << endl
         << "a > b is "                       << a << ">"       << b << "and the result is " << (a > b) << endl
         << "a < b is "                       << a << ">"       << b << "and the result is " << (a < b) << endl
         << "a == b is "                      << a << "=="      << b << "and the result is " << (a == b) << endl
         << "a >= b is "                      << a << ">="      << b << "and the result is " << (a >= b) << endl
         << "a <= b is "                      << a << "<="      << b << "and the result is " << (a <= b) << endl
         << "a != b is "                      << a << "!="      << b << "and the result is " << (a != b) << endl;
    return 0;
}

