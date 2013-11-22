//
// main.cpp
// Task2
//
// Created by Andrey Kovalev on 01.11.13.
// Copyright (c) 2013 Andrey Kovalev. All rights reserved.
//

//Задание 2

#include <iostream>
using namespace std;
class X
{
    public:
        X(){++s_count;};
        ~X(){--s_count;};
 
        static const int& count(){return s_count;};
    private:
        static int s_count;
};

int X::s_count = 0;

int main(int argc, const char * argv[])
{
    X a1;
    X a2;
    X* pa3 = new X();
    cout << X::count() << '\n';
    delete pa3;
    cout << a1.count() << '\n';
    return 0;
}