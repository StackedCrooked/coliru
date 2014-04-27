#include <iostream>
#include <vector>
#include "stdio.h"
using namespace std;


class A
{
    int a_;
public:
	int geta() { return a_;}
};


class B:public A
{
	int b_;
public:
	int getb() { return b_;}
};

A g_a;
B g_b;



int main()
{
	

	std::vector<A> veca(1);

	std::vector<B> vecb(1);
	std::cout << veca[0].geta()<<" "<<vecb[0].geta() << " " << vecb[0].getb() << std::endl;

    A a;
	B b;

	std::cout << a.geta()<<" "<<b.geta() << " "<<b.getb() << std::endl;
	std::cout << g_a.geta()<<" "<<g_b.geta() <<" "<<g_b.getb()<<std::endl;
 	return 0;
}