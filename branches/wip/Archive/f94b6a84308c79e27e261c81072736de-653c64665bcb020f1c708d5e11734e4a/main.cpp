#include <iostream>
#include <algorithm>

using namespace std;

int upper(char upper)
{
    return toupper(upper);
}

int main()
{
    string str = "Now";

    transform(str.begin(), str.end(), str.begin(), upper);

    cout<<str;

    return 0;
}