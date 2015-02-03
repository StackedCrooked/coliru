#include <iostream>
#include <string>

using namespace std;

void erase_all( string& str, const string& substr )
{
    while(true)
    {
        auto p = str.find(substr);
        if( p == string::npos ) return;
        str.erase( p, substr.length() );
    }
}

int main()
{
    string s;
    cin >> s;
    erase_all( s, "WUB" );
    cout << s;
}