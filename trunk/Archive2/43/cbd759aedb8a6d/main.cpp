#include <iostream>
#include <memory>

class child_impl {
public:
    child_impl()
		: value_(0)
	{
	}

	void print_value()
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

class child_impl_ptr {
public:
	child_impl_ptr()
		: impl_(std::make_shared<child_impl>())
	{
	}

	child_impl& operator*()
	{
		return *impl_.get();
	}

	child_impl* operator->()
	{
		return impl_.get();
	}

	child_impl* get()
	{
		return impl_.get();
	}

private:
	std::shared_ptr<child_impl> impl_;
}; /* class child_impl_ptr */

class child {
public:
	child()
		: impl_(nullptr)
	{
	}

	child(const child& other)
		: impl_(other.impl_ ? new child_impl_ptr(*other.impl_) : nullptr)
	{
	}

	child(const child_impl_ptr& other)
		: impl_(new child_impl_ptr(other))
	{
	}

	~child()
	{
		delete impl_;
	}

	void print_value()
	{
		impl_->get()->print_value();
	}

	child& operator=(const child& other)
	{
		if (this != &other) {
			delete impl_;
			impl_ = other.impl_ ? new child_impl_ptr(*other.impl_) : nullptr;
		}
		return *this;
	}

	child& operator=(const child_impl_ptr& other)
	{
		if (impl_ != &other) {
			delete impl_;
			impl_ = new child_impl_ptr(other);
		}
		return *this;
	}

private:
	child_impl_ptr* impl_;
}; /* class child */

class parent {
public:
	child get_child() const
	{
		return child_;
	}

	void set_value(int value)
	{
		child_->set_value(value);
	}

private:
	child_impl_ptr child_;
}; /* class parent */

int main(int argc, char* argv[])
{
	child c;

	{
		parent p;

		c = p.get_child();
		c.print_value();

		p.set_value(1337);
	}

	c.print_value();

	return 0;
}
