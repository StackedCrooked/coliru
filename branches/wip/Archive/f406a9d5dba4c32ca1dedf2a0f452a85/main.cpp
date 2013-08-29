#include <iostream>

using namespace std;
int main()
{
    cout << "Hello GCC " << __VERSION__ << "!" << endl;
    char a = 0;
    cout << "Are you busy (y/n) ?" << endl;
    cin >> a;
    switch(a)
    {
        case 'y':
        case 'Y':
            cout << "Ok Carryon..." << endl;
            break;
        case 'n':
        case 'N':
            cout << "Then come here..." << endl;
            break;
        default:
            cout << "Invalied answer!" << endl;
    }
}