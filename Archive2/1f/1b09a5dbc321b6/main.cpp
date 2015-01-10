#include <iostream>

struct Base
{
    virtual std::ostream& display(std::ostream& os) const = 0;
	friend std::ostream& operator<<(std::ostream& lhs, const Base& rhs)
	{
		return rhs.display(lhs);
	}
};

struct A: Base
{
	virtual std::ostream& display(std::ostream& os) const
	{
		return os << "A" << std::endl;
	}
};

struct B: A
{
	virtual std::ostream& display(std::ostream& os) const
	{
		return os << "B" << std::endl;
	}
};

int main()
{
	A a;
	std::cout << a << std::endl;

	B b;
	std::cout << b << std::endl;
}