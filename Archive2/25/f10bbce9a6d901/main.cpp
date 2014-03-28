#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Herp {
    public:
    string internal;
        const Herp& operator=(const string& s)
        {
            cout<<"Standard initialize operator\n";
            internal = s;
            return *this;
        }
        const Herp& operator=(string&& s)
        {
            cout<<"Move initialize operator\n";
            internal = s;
            return *this;
        }
};

int main()
{
    Herp a;
    stringstream ss;
    ss<<string("abcdef");
    a = ss.str();
    cout <<"ss: " << ss.str() << " internal: " << a.internal << endl;
    cout << (void*)ss.str().c_str() << endl;
    cout << (void*)a.internal.c_str() << endl;
    return 0;
}