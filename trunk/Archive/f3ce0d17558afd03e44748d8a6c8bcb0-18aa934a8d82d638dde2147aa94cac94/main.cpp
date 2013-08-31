#include <iostream>
#include <thread>
#include <vector>
#include<boost/variant.hpp>
#include <boost/variant/recursive_wrapper.hpp>

//Can this be solved with a recursive_wrapper?

typedef boost::variant<std::vector<int>, std::vector<std::string>, std::vector<Structure> > Container;

typedef std::pair<std::string, Container > Structure;



int main()
{
    
    std::cout << "Hello GCC " << __VERSION__ << "!" << std::endl;
}