#include <iostream>

class NonCopyable
{
public:
    NonCopyable()
	{
	}

private:
	NonCopyable(NonCopyable const&) /* delete */;
	NonCopyable & operator=(NonCopyable const &) /* delete */;

public:
	void test()
	{
		NonCopyable nc;
		NonCopyable nd = nc;
	}
};

int main()
{
	NonCopyable n;
	n.test();
	return 0;
}