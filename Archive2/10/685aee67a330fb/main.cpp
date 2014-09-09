#include <iostream>
using namespace std;
 
int main()
{
    double A, B, C, D, E, F;

    A = 12.95;
    B = 24.95;
    C = 6.95;
    D = 14.95;
    E = 3.95;
    F = A + B + C + D + E;

    //displays each item's price
    cout << "Item A cost $" << A << endl;
    cout << "Item B cost $" << B << endl;
    cout << "Item C cost $" << C << endl;
    cout << "Item D cost $" << D << endl;
    cout << "Item E cost $" << E << endl;
    cout << "*********************************" << endl;
    cout << "\n";

    //displays subtotal
    cout << "The subtotal is $" << F << endl;
   
    //displays the total tax
    //Variable F is total
    cout << "The total sales tax is $" << cout.precision(2) << F*.06 << endl;

    //diplays total price
    cout << "Your total cost is $" << F + F*.06 << endl;

    cin >> A;
    return 0;
}