#include <iostream>
#include <string>
#include <vector>


std::string increment(std::string s)
{
    if (s.empty()) return s;
    
    long i = s.size() - 1;
    while (i >= 0)
    {
        if (s[i] == '9')
        {
            s[i] = '0';
            i--;
        }
        else if (s[i] >= '0' && s[i] <= '8')
        {
            s[i]++;
            return s;
        }
        else
        {
            i--;
        }
    }
    return s;
}


int main()
{
    std::string s = "001";
    for (int i = 1; i <= 1000; ++i)
    {
        std::cout << s << (i % 10 == 0 ? '\n' : ' ');
        s = increment(s);
    }
}
