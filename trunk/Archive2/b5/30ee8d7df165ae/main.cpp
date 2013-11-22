#include <iostream>
#include <string>
#include <vector>


void increment(char* begin, char* end)
{
    auto length = end - begin;
    
    long i = length - 1;
    while (i >= 0)
    {
        char& c = begin[i];
        if (c == '9')
        {
            c = '0';
            i--;
        }
        else if (c >= '0' && c <= '8')
        {
            c++;
            return;
        }
        else
        {
            // invalid character
            return;
        }
    }
}


int main()
{
    std::string s = "001";
    for (int i = 1; i <= 1000; ++i)
    {
        std::cout << s << (i % 10 == 0 ? '\n' : ' ');
        increment(&*s.begin(), &*s.end());
    }
}
