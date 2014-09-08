#include <iostream>
#include <sstream>
#include <boost/regex.hpp>

enum Test {
    A = 0,
    B = 1
};

struct S {
    Test test;
};
class BaseException : public std::exception
{
};

class MyException : public BaseException
{
};

int main() {
    //boost::regex expression("^(1|0)");
    S s;
    if(s.test){
      std::cout << s.test << std::endl; 
    }
 
  
	return 0;
}
