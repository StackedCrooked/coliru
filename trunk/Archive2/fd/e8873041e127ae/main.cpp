#include <iostream>

class child {
public:
    virtual ~child() {}
	virtual void print_value() const = 0;
}; /* class child */

class child_impl : public child {
public:
	child_impl()
		: value_(0)
	{
	}

	virtual void print_value() const
	{
		std::cout << "value_ = " << value_ << "\n";
	}

	void set_value(int value)
	{
		value_ = value;
	}

private:
	int value_;
}; /* class child_impl */

class parent {
public:
	const child& get_child() const
	{
		return child_;
	}

	void set_value(int value)
	{
		child_.set_value(value);
	}

private:
	child_impl child_;
}; /* class parent */

int main(int argc, char* argv[])
{
	parent p;
	p.get_child().print_value();

	p.set_value(1337);
	p.get_child().print_value();

	return 0;
}
