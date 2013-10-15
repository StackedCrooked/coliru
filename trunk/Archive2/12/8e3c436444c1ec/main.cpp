#include <stdio.h>
#include <iostream>
using namespace std;

class object{
    object(const object&) = delete;
    object& operator=(const object&) = delete;
public:
    object(const object&&){}
    object& operator=(const object&&) = delete;

    object(){}

};

int main()
{
    throw object();
}