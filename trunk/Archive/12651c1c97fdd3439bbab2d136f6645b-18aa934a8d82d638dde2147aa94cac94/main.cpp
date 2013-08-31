#include <boost/exception/all.hpp>

struct my_exception: virtual std::exception, virtual boost::exception {};

struct my_exception2: virtual std::exception, virtual boost::exception {
    virtual const char* what() const throw() {
        return "WHAT";
    }
};

struct my_exception3: virtual std::exception, virtual boost::exception {
    virtual const char* what() const throw() {
        return boost::diagnostic_information(this).c_str();
    }
};

int main() {
    try {
        BOOST_THROW_EXCEPTION(my_exception());
    } catch (const std::exception& e){
        std::cout << e.what() << std::endl; //This is useless ___ std::exception
    }
    
    try {
        BOOST_THROW_EXCEPTION(my_exception());
    } catch (const boost::exception& e){
        std::cout << boost::diagnostic_information(e) << std::endl; //This is what I'd like to see ___ main.cpp(39): Throw in function int main() ___ Dynamic exception type: boost::exception_detail::clone_impl ___ std::exception::what: std::exception
    }
    
    try {
        BOOST_THROW_EXCEPTION(my_exception2());
    } catch (const std::exception& e){
        std::cout << e.what() << std::endl; //Overriding what usually works ___ WHAT
    }
  
    try {
        BOOST_THROW_EXCEPTION(my_exception3());
    } catch (const std::exception& e){
        std::cout << e.what() << std::endl; //But somehow here it does not work ___ Unknown exception.
    }
}