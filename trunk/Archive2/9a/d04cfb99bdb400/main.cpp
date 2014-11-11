#include <string>
using namespace std;

struct first
{
public:
    const string &str;
    first(const string & str) : str(str)     {    }
};

struct second : public first
{
public:
    const string &str2;
    second(const string &str1, const string &str2) : first(str1), str2(str2)
    {    }
};

template<typename T> class base;

template<> class base<first> {
public:
    inline static first fun(const string &s1, const string &s2) {
        return first(s1);
    }
};

template<> class base<second> {
public:
    inline static second fun(const string &s1, const string &s2) {
        return second(s1, s2);
    }
};

int main()
{
    string a = "a";
    string bb = "b";
    first f = base<first>::fun(a, bb);
    second s = base<second>::fun(a, bb);
   
    return 0;
}