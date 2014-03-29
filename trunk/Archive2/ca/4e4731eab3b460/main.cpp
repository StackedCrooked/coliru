#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Herp {
    string internal;
    public:
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
    cout <<"ss: " << ss.str() << endl;
    cout << ss << endl;
    cout << &a << endl;
    return 0;
}