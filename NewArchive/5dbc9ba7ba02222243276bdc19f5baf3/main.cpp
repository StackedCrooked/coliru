#include <limits>
#include <iostream>
#include <memory>
#include <functional>

using std::cout;
using std::endl;


struct base
{
    virtual void func() { cout << "base\n"; }
};
struct derived: base
{
	void func() override { cout << "derived\n"; }
};

int main()
{
	base b;
	derived d;

	std::function<void(base*)> f(std::mem_fn(&base::func));

	f(&b);
	f(&d);
}