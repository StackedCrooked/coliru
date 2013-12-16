#include <iostream>
#include <string>
#include <stdexcept>

#include <boost/cstdlib.hpp>
#include <boost/exception/exception.hpp>
#include <boost/exception/diagnostic_information.hpp>

struct A {};

struct B : boost::exception {};

int main()
{
    std::cout << "throw A" << std::endl;
    try {
        throw A();
    }
    catch (...)
    {
    	std::string str = boost::current_exception_diagnostic_information();
    	std::cout << str << std::endl;
    }

    std::cout << std::endl;


    std::cout << "throw B" << std::endl;
    try {
    	throw B();
    }
    catch (...)
    {
    	std::string str = boost::current_exception_diagnostic_information();
    	std::cout << str << std::endl;
    }

    std::cout << std::endl;


    std::cout << "throw std::runtime_error" << std::endl;
    try {
    	throw std::runtime_error("test runtime error exception");
    }
    catch (...)
    {
    	std::string str = boost::current_exception_diagnostic_information();
    	std::cout << str << std::endl;
    }

    return boost::exit_success;
}
