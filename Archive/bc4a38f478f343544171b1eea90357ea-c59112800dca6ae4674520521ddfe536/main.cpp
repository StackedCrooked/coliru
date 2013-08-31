#include<iostream>
#include<ostream>
#include<cstdio>
using namespace std;

class Base1
{
public:
    Base1():a(1){}
	virtual ~Base1()
	{
		cout << "~Base1"  << endl;
	}
	int a;
	virtual void print()
	{
		cout << "I am base 1!" << endl;
	}
};

class Base2
{
public:
	Base2():b(2){}
	virtual ~Base2(){
		cout << "~Base2" << endl;
	}
	int b;
	virtual void print()
	{
		cout << "I am base 2!" << endl;
	}
};

class Derive : public Base1, public Base2
{
public:
	Derive():c(3){}
	virtual ~Derive(){
		cout << "~Derive" << endl;
	}
	int c;
	virtual void print()
	{
		cout << "I am Derive!!" << endl;
	}
	void prints()
	{
		cout << "I am not virtual!!" << endl;
	}
};

int main()
{
	Derive *d = new Derive();
    //d->~Derive();
    
    size_t addr = (size_t)&(*d);

    size_t addr_a = addr + 8;
	std::cout << *(int*)addr_a << std::endl;

	size_t addr_b = addr + 24;
	std::cout << *(int*)addr_b << std::endl;

	size_t addr_c = addr + 28;
	std::cout << *(int*)addr_c << std::endl;
    
    /*__asm__ (
        "movq -24(%rbp), %rax \n\t"
        "movq (%rax), %rax \n\t"
        "addq $0, %rax \n\t"
        "movq (%rax), %rax \n\t"
        "movq -24(%rbp), %rdx \n\t"
        "movq %rdx, %rdi \n\t"
        "call *%rax"
    );*/
    
	std::cin.get();
	return 0;
}