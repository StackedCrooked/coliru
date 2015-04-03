#include <iostream>
#include <sstream>
#include <cstring>

using namespace std;

string real_write(const char* userString, ...)
{
    ostringstream ss;
    int formatLen = strlen(userString);
    const char* end = userString+formatLen;
    const char* it;

    char target1 = '{';
    char target2 = '}';

    va_list arguments;    
    va_start(arguments, userString);

    for (it = userString; it < end; ++it)
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
template<class...Ts>
string write(string const& userString, Ts...Vs)
{return real_write(userString.c_str(), (double)Vs...);}

int main()
{
    cout << write("This is {0} a string. {1} {3}", 5, -1.9, 'n') << '\n';
}