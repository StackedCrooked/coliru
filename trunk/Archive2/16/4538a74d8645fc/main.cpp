#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::string;
using std::vector;

void foo(const string& lhs, const string& rhs)
{
    vector<string> strv;
    strv.push_back(lhs);
    strv.push_back(rhs);
    
    if (strv[0].compare(strv[1]) == 0)
        cout << "the same\n";
    else
        cout << "different\n";
}

int main()
{
    foo("A", "A");
    foo("A", "B");
}