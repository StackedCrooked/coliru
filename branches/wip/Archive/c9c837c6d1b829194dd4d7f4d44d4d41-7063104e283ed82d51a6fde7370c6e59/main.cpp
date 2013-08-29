#include <iostream>
#include <memory>

using namespace std;

class abstract
{
public:
    abstract() 
	{
	}

	virtual void something() = 0;
};

class sub : public abstract
{
public:
	sub() 
	{
	}

	void something()
	{
		cout << "Works!" << endl;
	}
};

int main()
{
	unique_ptr<sub> s(new sub);

	s->something();

	cin.get();
	return 0;
}