#include <stdio.h>
#include <iostream>
using namespace std;

class object{
    object(const object&);
    object& operator=(const object&);
public:
    object(const object&&){}
    object& operator=(const object&&){}

    object(){}

};

int main()
{
    throw object();
}