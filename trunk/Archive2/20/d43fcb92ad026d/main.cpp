class Base
{
public:
    void foo () { }
protected:
	void bar () { }
private:
	void baz () { }
};

class Derived : public Base
{
	void mumble()
	{
    		foo();              	//1
    	bar();              	//2
    		baz();              	//3
	}
};

int main()
{
	Base b;                 	//4
	Derived d;              	//5

	b.foo();                	//6
	d.foo();                	//7

	b.bar();                	//8
	d.bar();                	//9

	b.baz();                	//10
	d.baz();                	//11
}