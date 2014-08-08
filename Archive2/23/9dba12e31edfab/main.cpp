/*
* main.cpp
*
 *  Created on: Aug 7, 2014
 *      Author: luke
 */
#include <iostream>
#include <cstdlib>
using namespace std;

class abs2
{
    int a,b;

public:
    void unregister(){
        a = 0;
        b = 0;
    }
    void erase(){
        a = 2;
        b = 0;
    }
    abs2(int c,int d) {}
};
/*
abs::abs(int c,int d){
    a = c;
    b = d;
}*/
int main () {
    abs2 obj(4, 2);

    obj.unregister();
    obj.erase();
}