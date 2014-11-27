#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include <memory>

using namespace std;

template <class T> void foo(T *);

void foo(int *);

template void foo<float>(float *);
void foo(float *);


int main()
{
    double i;
    foo(&i);

}


template <class T>
void foo(T *){ cout << "template foo" << endl; }

void foo(int *){ cout << "simple foo" << endl; }

//template<>
//void foo<float>(float *){ cout << "specialized float foo" << endl; }
void foo(float *){ cout << "simple float foo" << endl; }
