#include<iostream>
#include<map>
#include<set>
#include<string>
#include<algorithm>
#include<iterator>
#include<utility>
#include <stdio.h>
#include <string.h>

class foo
{
    public:
    static const std::string stconst = "foo";
};
int main()
{
    foo f;
    std::cout << f.stconst;
}