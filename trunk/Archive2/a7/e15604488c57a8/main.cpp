#include <iostream>
#include <string>
#include <algorithm>

using namespace std;


string toLowerCase(string s)
{
    std::transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}


bool operator <<(const string& member, const string& player)
{
    return toLowerCase(member) == toLowerCase(player);
}



int main()
{
    bool b = string("Hi") << string("hi");

    cout << b;

}