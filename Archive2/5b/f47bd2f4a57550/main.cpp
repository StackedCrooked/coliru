#include <iostream>
#include <string>
#include <string.h>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    for (auto& el : vec)
    {
        os << el << ' ';
    }
    return os;
}

char * reverse(char * begin, char * end) {
    if(begin >= end) return end;
    end--;
    char * p = begin;
    while(begin < end) {
        char t = *begin;
        *begin = *end;
        *end = t;
        begin++;
        end--;
    }
    return p;
}

int main()
{
    char s[] = "Hello world one two three";
    std::cout << reverse(s, s + strlen(s)) << std::endl;
    std::cout << reverse(s, s + strlen(s)) << std::endl;
/*    std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << "Hello world" << std::endl;
    int i = 5;
    int *p = &i;
    int x = 0;
    std::cout << (*p)++ << std::endl;
    std::cout << (*p)++ << std::endl;*/
}
