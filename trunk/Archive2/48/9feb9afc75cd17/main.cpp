//============================================================================
// Name        : BindThread.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <functional>
using namespace std;



//using IntPtr3 = [](int)->int;
using IntPtr2 = int(int);




int PrintValue(IntPtr2 n)
{
    return n(8);
}

int PrintInt(int n)
{
	printf("%d\n",n);
    return 666;
}

int main()
{
	PrintValue(nullptr);


	return 0;
}
