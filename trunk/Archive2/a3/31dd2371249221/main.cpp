#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    string s = "1,0";
    string result;

    //result.resize(s.length());
    replace_copy(s.begin(), s.end(), back_inserter<std::string>(result), ',', '.');

    cout << '"' << result         << '"' << endl;
    cout << '"' << result.c_str() << '"' << endl;
    cout << result.length() << endl;
}