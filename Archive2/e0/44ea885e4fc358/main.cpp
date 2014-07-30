#include <iostream>
#include <string>
using namespace std;

char _getch();
char RESTART;

string& Get_Filename()
{
    char ch;
    string name;

    while (ch = _getch() != 'CR')
    {
        if (ch == 'ESC')
            throw RESTART;
        if (ch == 'BS')
        {
            name.pop_back();
            cout << 'BS';   // Also, will this correctly delete or will I need to
        }                   // << '\b' << ' ' << '\b'?
        else
        {
            name += ch;
            cout << ch;
        }
    }
    return name;
}

int main() {}