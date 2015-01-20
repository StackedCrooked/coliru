#include <stdarg.h>
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
	CallbackPack(void * ptr = nullptr, unsigned int i = 0, unsigned int * sizes = nullptr) :
		callback(ptr), argv(i), argSizes(sizes) {}

	void * callback;
	unsigned int argv;
	unsigned int * argSizes;
};

std::map<std::string, CallbackPack> g_callbacks;

void AddCallback(std::string str, void * callback, unsigned int argv, ...)
{
	va_list pArg;
	va_start(pArg, argv);

	auto ptr = new unsigned int[argv];
	for (unsigned int i = 0; i < argv; i++) {
		ptr[i] = va_arg(pArg, unsigned int);
	}

	g_callbacks[str] = CallbackPack(callback, argv, ptr);

	va_end(pArg);
}

void DoSomething(std::string dest, ...)
{
	CallbackPack & f = g_callbacks[dest];
	void * callback = f.callback;
	int argv = f.argv;
	unsigned int * argSizes = f.argSizes;

	va_list pArg;
	va_start(pArg, dest);

	unsigned int _[6] = {0u};

	for (int i = 1; i < argv; i++) {
		_[i] = _[i - 1] + ((argSizes[i - 1] + sizeof(int) - 1) & ~(sizeof(int) - 1));
	}

	if (argv == 0)
		((void(*)(...))callback)();
	else if (argv == 1)
		((void(*)(...))callback)(pArg + _[0]);
	else if (argv == 2)
		((void(*)(...))callback)(pArg + _[0], pArg + _[1]);
	else if (argv == 3)
		((void(*)(...))callback)(pArg + _[0], pArg + _[1], pArg + _[2]);
	else if (argv == 4)
		((void(*)(...))callback)(pArg + _[0], pArg + _[1], pArg + _[2], pArg + _[3]);
	else if (argv == 5)
		((void(*)(...))callback)(pArg + _[0], pArg + _[1], pArg + _[2], pArg + _[3], pArg + _[4]);

	va_end(pArg);
}

void func_5(char &ch, double &t, std::string *&str, MyClass *&m, long long &ll)
{
	std::cout << "====FUN_5===: " << std::endl;
	std::cout << "1.char: " << ch << std::endl;
	std::cout << "2.float?: " << t << std::endl;
	std::cout << "3.str: " << *str << std::endl;
	std::cout << "4.Class * [99]\\[1]: " << (*m).GetI(99) << ',' << (*m).GetI(1) << std::endl;
	std::cout << "5.ll: " << ll << std::endl;
	*str += "DEF";
	(*m).SetI(1, 2);
}

void func_2(const short &s, const double &d)
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
	m.SetI(1, 100);

	std::string str("ABC");

	std::cout << "Size int: " << sizeof(int) << std::endl;
	std::cout << "Size float *: " << sizeof(float *) << std::endl;
	std::cout << "Size std::string : " << sizeof(std::string ) << std::endl;
	std::cout << "Size std::string &: " << sizeof(std::string &) << std::endl;
	std::cout << "Size std::string &&: " << sizeof(std::string &&) << std::endl;
	std::cout << "Size const std::string *: " << sizeof(const std::string *) << std::endl;


	AddCallback("CALLBACK_5", (void *)func_5, 5, sizeof(char), sizeof(double), sizeof(std::string *), sizeof(MyClass *), sizeof(long long));
	DoSomething("CALLBACK_5", 'C', 10.01, &str, &m, 0xffffffffffffffffull );

	AddCallback("CALLBACK_0", (void *)func_0, 0);
	DoSomething("CALLBACK_0");

	AddCallback("CALLBACK_1", (void *)func_2, 2, sizeof(short), sizeof(double));
	DoSomething("CALLBACK_1", 32768, 10.01);

	std::cout << "=========\nstr: " << str << std::endl;
	std::cout << "m[1]: " << m.GetI(1) << std::endl;

	return 0;
}


