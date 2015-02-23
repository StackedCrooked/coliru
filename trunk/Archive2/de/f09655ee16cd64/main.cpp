//#include "stdafx.h"
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

struct product
{
string name;
}family[50];

int main()
{
    //family[1] == head of house hold
    cout << "please enter your name and first inital please" << endl;
    cin >> family[1].name;
    cout << family[1].name;
}
