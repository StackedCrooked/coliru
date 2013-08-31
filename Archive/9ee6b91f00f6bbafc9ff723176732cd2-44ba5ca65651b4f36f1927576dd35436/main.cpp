#include <iostream>
using namespaces std;

class String
{
    char* arr;
    int len;

    friend ostream& operator << (ostream& s, const String& c) {
        return s << c.arr;
    }

    Public:
        String() : len(0), arr(0)
        {
        }
        String(const char* name)
        {
            *arr = *name;
        }
};

int main()
{
    String s;
    cout << s << endl;
}