#include <iostream>
#include <stddef.h>
#include <utility>

struct String
{
public:
    typedef char value_type;
	typedef size_t size_type;
	typedef value_type & reference;
	typedef const value_type & const_reference;

	// construct empty string
	String()
	{
		std::cout << "Default constructor." << std::endl;
	}

	// construct by copying
	String(const String & other)
	{
		std::cout << "Copy constructor." << std::endl;
	}

	// construct by moving
	String(String && other)
	{
		std::cout << "Move constructor." << std::endl;
	}

	// destruct
	~String()
	{
		std::cout << "Destructor." << std::endl;
	}

	// subscript mutable sequence
	reference operator[](size_type pos)
	{
		std::cout << "operator[" << pos << "]." << std::endl;
		return this->storage;
	}

	// subscript nonmutable sequence
	const_reference operator[](size_type pos) const
	{
		std::cout << "operator[" << pos << "] const." << std::endl;
		return this->storage;
	}

	// return size
	size_type size() const
	{
		std::cout << "size" << std::endl;
		return size_type(1);
	}

private:
	value_type storage;
};

size_t someFunction(const String & e)
{
	size_t length = e.size();
	size_t sum = 0;
	for (size_t i = 0; i < length; ++i)
	{
		sum += e[i];
	}
	size_t someCode = sum;
	return someCode;
}

int main()
{
	String e;
	someFunction(e);
}
