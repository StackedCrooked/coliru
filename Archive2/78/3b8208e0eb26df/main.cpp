#include <iostream>
#include <string>
#include <cstdarg>

using namespace std;
//Prototype
string write(string userString...);

void main()
{
    write("This is {0} a string.{1}", 5);
    system("pause");
}
string write(string userString...)
{
    char target1 = '{';
    char target2 = '}';

    va_list arguments;

    va_start(arguments, userString);
    for (int i = 0; i < userString.size(); ++i)
    {
        if (userString[i] == target1 & userString[i + 2] == target2)
        {
        //Need help here...



        }
    }
    va_end(arguments);
    return userString;
}