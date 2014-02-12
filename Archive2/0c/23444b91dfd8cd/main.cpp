#include <iostream>

class BaseException : public std::exception
{
};

class MyException : public BaseException
{
};

int main() {

	try
	{
		throw MyException();
	}
	catch (BaseException* e)
	{
		std::cout << "BaseException" << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "exception" << std::endl;
	}
	catch (...)
	{
		std::cout << "catch all" << std::endl;
	}
	return 0;
}
