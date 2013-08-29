#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct S
{
    S(){}
    S(S const&){std::cout << "Found the const& copy constructor" << std::endl;}
    template<typename T> explicit S(T&&) {std::cout << "Found a random constructor" << std::endl;}

#ifndef MULTIPLE_CCS
    S(S&) {std::cout << "Found the non const copy constructor!" << std::endl;}
#endif
};

int main()
{
    S s;
    S s2(const_cast<S const&>(s));
    S s3(s);
}
