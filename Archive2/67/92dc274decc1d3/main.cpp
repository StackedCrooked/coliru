#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;

int main()
{
    string s = " abc";

    find_if(s.begin(), s.end(), static_cast<int(*)(int)>(isspace));
}
