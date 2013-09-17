
#include <iostream>
#include <string>

using namespace std;

decltype(auto) f()
{
    string s = "lol";
    return s;
}

void g(string &)
{
    cout << "string &" << endl;
}

void g(string const&)
{
    cout << "string const&" << endl;
}

void g(string &&)
{
    cout << "string &&" << endl;
}

void g(string const&&)
{
    cout << "string const&&" << endl;
}

int main()
{
    decltype(auto) s = f();
    g(s);
    return 0;
}