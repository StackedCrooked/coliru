#include <memory>
#include <array>
#include <tuple>
#include <iostream>
#include <vector>
#include <type_traits>

using std::cout;
using std::endl;

class base
{
public:

    virtual void func(int n = 5) = 0;
};

class derived: public base
{
public:

	virtual void func(int n = 7)
	{
		cout<<n<<endl;
	}
};

int main()
{
	cout<<std::boolalpha;

	auto p = std::unique_ptr<base>( new derived);

	p->func();
}