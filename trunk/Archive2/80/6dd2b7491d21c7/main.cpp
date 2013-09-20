#include <cstdio>
#include <string>
#include <vector>

int main(int, char**)
{
    std::vector<std::string> vec;
    vec.push_back("foo");
    vec.push_back("bar");
    vec.push_back("baz");

    puts("C++03");
    typedef std::vector<std::string>::const_iterator citer_t;
    for (citer_t it = vec.begin(); it != vec.end(); ++it)
    {
        puts(it->c_str());
    }

    puts("");
    puts("C++11");
    // c[begin, end, rbegin, rend] have been added to STL containers in C++11
    for (auto it = vec.crbegin(); it != vec.crend(); ++it)
    {
        puts(it->c_str());
    }

    return 0;
}
