#include <iostream>

using namespace std;

int main (int argc, char *argv[])
{ 
    char quit;  

    quit = '\0';
    while (quit != 'q')
    {
        cout << "Hello ! This is a console app." << endl;
        cout << "To create a console, go to Project Options and select" << endl;
        cout << "\'Win32 Console\'." << endl;
        cout << "Press q to quit " << endl;
        cin >> quit;
    }

    return 0;
}