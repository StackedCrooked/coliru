#include <iostream>
#include <string>

template<typename T>
class named_parameter {
public:
    explicit named_parameter(T value)
		: value_(value) {}

	operator T() { return value_; }

private:
	T value_;
}; /* class named_parameter */

typedef named_parameter<bool> should_print;

class object {
public:
    object(should_print should_print = should_print(false))
    {
        if (should_print)
            std::cout << "Oh, hi!\n";
    }
}; /* class object */

int main()
{
    //object o;
    object o(should_print(true));
    return 0;
}
