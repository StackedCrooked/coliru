#include <iostream>
#include <string>
#include <vector>

struct Str {
    int a;
    int b;
};

std::vector<Str> vec;

void add() {
        Str str;
        str.a=10;
        vec.push_back(str);
}

int main()
{
    add();
    std::cout<<vec.at(0).a;
}

