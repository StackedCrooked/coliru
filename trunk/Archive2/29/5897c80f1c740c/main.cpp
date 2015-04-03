#include <cstdarg>

#include <string>
#include <iostream>
#include <sstream>

using namespace std;

string write(string const& userString, ...)
{
    ostringstream ss;
    string::const_iterator it;

    char target1 = '{';
    char target2 = '}';

    va_list arguments;    
    va_start(arguments, userString);

    for (it = userString.begin(); it < userString.end(); ++it)
    {
        if ((*it == target1) & (*(it + 2) == target2))
        {
            double val=va_arg(arguments,double);
            ss << val;
            it += 2;  // remember its incremented by the loop aswell
        } else
        {
            ss << *it;
        }
    }

    va_end(arguments);
    return ss.str();
}

int main()
{
    cout << write("This is {0} a string. {1}", 5.0, -1.9) << '\n';
}