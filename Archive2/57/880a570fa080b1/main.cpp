#include <iostream>
using namespace std;

int main()
{
    float a, b, ans;
    int   choice;

    cout<< "[1] For Addition\n[2] For Subtraction\n[3] For Multiplication\n[4] For Division\n [5] to Exit " <<endl;

    // while a number is not entered or choice is less than
    // 1 or choice is greater than 5
    while( !(cin >> choice) || (choice < 1 || choice > 5) )
    {
        cout << "Invalid Choice.\n";
        cin.clear();          // clear error state
        cin.ignore(100,'\n'); // ignore 100 characters or until newline is found
    }

    if( choice == 5 ) return 0; // exit

    cout << "Enter two values: " << endl;

    // while the character entered are not numbers
    while( !(cin >> a >> b) )
    {
        cout << "Not a number, enter again" << endl;
        cin.clear();
        cin.ignore(100, '\n');
    }

    switch( choice )
    {
    case 1 : ans = a + b; break;
    case 2 : ans = a - b; break;
    case 3 : ans = a * b; break;
    case 4 : ans = a / b; break;
    }

    cout << "answer is " << ans; // yay
}
