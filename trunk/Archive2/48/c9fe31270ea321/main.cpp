#include <map>
#include <functional>
#include <iostream>
#include <assert.h>
using namespace std;

typedef function<void*(void)> _Constructor;

class class_factory
{
public:
    static map<string, _Constructor> class_can;
	static void add_class_ctor(const string& class_name, const _Constructor& _ctor) //增加类
	{
        cout << "insert!" << endl;
		class_can.insert(make_pair(class_name, _ctor));
	}
	static _Constructor get_class_ctor(const string& class_name) //根据类名找到类
	{
		auto it = class_can.find(class_name);
		if (it != class_can.end())
		{
            cout << "find!" << endl;
			return it->second;
		}
        cout << "not find!" << endl;
		return function<void*(void)>();
	}
};
map<string, _Constructor> class_factory::class_can; //初始化静态map


class class_register_impl
{
public:
	class_register_impl(const string& class_name, const _Constructor& _ctor)
	{
        cout << "construct class_register_impl" << endl;
		class_factory::add_class_ctor(class_name, _ctor);
	}
    void do_nothing(){}
};

template<typename _Class_Type,char class_name[]>
class class_register
{
public:
	static class_register_impl cr_impl;
    void do_nothing(){cr_impl.do_nothing();}
};
template<typename _Class_Type,char class_name[]>
class_register_impl class_register<_Class_Type, class_name>::cr_impl(class_name, [&](){return (void *)new _Class_Type; });

//在下面class_register<myclass>实例化模板的时候，静态变量cr_impl的初始化没有被调用，导致myclass类没加入到class_factory是为什么？
char class_name[] = "myclass";
class myclass : public class_register<myclass, class_name>
{
public:
    class_register<myclass, class_name> m_something;
    void nothing(){do_nothing();}
};


int main()
{
 	auto it = class_factory::get_class_ctor("myclass");
    myclass *p = (myclass *)it();
    delete p;
	return 0;
}