#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool is_space(char c)
{
    return c == ' ';
}

int main()
{
    string text = "This is the text";

    string::iterator it = find_if(text.begin(), text.end(), is_space);

    cout << *it << endl;

    return 0;
}