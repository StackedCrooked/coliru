#include <iostream>
#include <vector>
#include <bitset>
#include <tuple>
#include <map>
#include <array>
#include <functional>
#include <string>
#include <typeinfo>

bool f() {

    std::cout << "f";
    return true;
}

bool g() {

    std::cout << "g";
    return true;
}

int main() {


    if(f(),g())
    {
        std::cout<<"OK with ,";
    }

    std::cout<< std::endl;

    if(f()||g())
    {

        std::cout<<"OK with ||";
    }

    return 0;
}
