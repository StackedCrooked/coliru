#include <iostream>
#include <vector>

class object {
public:
    object()
		: value_(0)
	{
		std::cout << "object::object()\n";
	}

	object(const object& other)
		: value_(other.value_)
	{
		std::cout << "object::object(const object& other)\n";
	}

	object(object&& other)
		: value_(other.value_)
	{
		std::cout << "object::object(object&& other)\n";
	}

	~object()
	{
		std::cout << "object::~object()\n";
	}

	void set_value(int value)
	{
		value_ = value;
	}

	object& operator=(const object& other)
	{
		if (this != &other)
			value_ = other.value_;
		return *this;
	}

	object& operator=(object&& other)
	{
		if (this != &other)
			std::swap(value_, other.value_);
		return *this;
	}

private:
	int value_;
}; /* class object */

int main(int argc, char* argv[])
{
	std::vector<object> objects;
	objects.reserve(5);

	object o;
	o.set_value(1337);

	std::cout << "\nemplace_back constructed:\n";
	objects.emplace_back(o);

	std::cout << "\nemplace_back move constructed:\n";
	objects.emplace_back(std::move(o));

	std::cout << "\nemplace_back in-place:\n";
	objects.emplace_back();

	std::cout << "\npush_back:\n";
	objects.push_back(o);

	std::cout << "\npush_back move:\n";
	objects.push_back(std::move(o));
	std::cout << "\n";

	return 0;
}
