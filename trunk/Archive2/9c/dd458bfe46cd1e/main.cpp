#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>


class MyClass
{

public:
    MyClass(int s = 200) :
		Size(s),
		Ptr(new int[s])
	{}

	MyClass(const MyClass & src) :
		Size(src.Size),
		Ptr(new int[src.Size])
	{
		memcpy(Ptr, src.Ptr, Size);
	}

	~MyClass()
	{
		if(Ptr)
			delete Ptr;
	}

	MyClass & operator =(const MyClass & src)
	{
		Size = src.Size;
		memcpy(Ptr, src.Ptr, Size);
		return *this;
	}

	void SetI(int i, int n) {Ptr[i] = n;}

	int GetI(int i) const{return Ptr[i];}

private:

	int Size;
	int * Ptr;
};

// test...

struct CallbackPack {
	CallbackPack(void * ptr = nullptr, int i = 0) : 
		callback(ptr), argv(i){}

	void * callback;
	int argv;
};

std::map<std::string, CallbackPack> g_callbacks;

void AddCallback(std::string str, void * ptr, int n)
{
	g_callbacks[str] = CallbackPack(ptr, n);
}

void DoSomething(std::string dest, ...)
{
	CallbackPack & f = g_callbacks[dest];
	void * callback = f.callback;
	int argv = f.argv;

	va_list pArg;
	va_start(pArg, dest);

	union any {
		size_t _A;
		void * _B;
		float _C;
		double _D;
		unsigned char _E;
		unsigned short _F;
		unsigned long long _G;
	} _[6];

	for (int i = 0; i < argv; i++)
		_[i] = va_arg(pArg, any);

	if (argv == 0) 
		((void(*)(...))callback)();
	else if (argv == 1)
		((void(*)(...))callback)(_[0]);
	else if (argv == 2)
		((void(*)(...))callback)(_[0], _[1]);
	else if (argv == 3)
		((void(*)(...))callback)(_[0], _[1], _[2]);
	else if (argv == 4)
		((void(*)(...))callback)(_[0], _[1], _[2], _[3]);
	else if (argv == 5)
		((void(*)(...))callback)(_[0], _[1], _[2], _[3], _[4]);

	va_end(pArg);
}

void func_5(char ch, double t, const std::string &str, const MyClass &m, long long ll)
{
	std::cout << "====FUN_5===: " << std::endl;
	std::cout << "1.char: " << ch << std::endl;
	std::cout << "2.float?: " << t << std::endl;
	std::cout << "3.str: " << str << std::endl;
	std::cout << "4.Class&: " << m.GetI(99) << ',' << m.GetI(5) << std::endl;
	std::cout << "5.ll: " << ll << std::endl;
}

void func_2(const short s, const double d)
{
	std::cout << "====FUN_2===: " << std::endl;
	std::cout << "1.Short:" << s << std::endl;
	std::cout << "2.double:" << d << std::endl;
}

void func_0()
{
	std::cout << "====FUN_0===: " << std::endl;
	std::cout << "0.No Parm" << std::endl;
}

int main(void)
{

	MyClass m(100);
	m.SetI(99, -100);
	m.SetI(5, 1);

	AddCallback("CALLBACK_5", (void *)func_5, 5);
	DoSomething("CALLBACK_5", 'C', 10.01f, &*(new std::string("ABC")), &m, 0xffffffffffffffffull );

	AddCallback("CALLBACK_0", (void *)func_0, 0);
	DoSomething("CALLBACK_0");

	AddCallback("CALLBACK_1", (void *)func_2, 2);
	DoSomething("CALLBACK_1", 32768, 10.01);

	return 0;
}
