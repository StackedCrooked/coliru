#include <limits>
#include <iostream>
#include <memory>
#include <functional>

using std::cout;
using std::endl;


struct base
{
    virtual void func() =0;
};
struct derived: base
{
	void func() override { cout << "derived\n"; }
};

int main()
{
	derived d;

	std::function<void(base*)> f(std::mem_fn(&base::func));

	f(&d);
}