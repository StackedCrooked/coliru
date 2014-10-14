#include <iostream>
#include <sstream>
#include <typeinfo>

static std::ostringstream log;

template <typename T>
class Data {
public:
    Data() {
        log << "in Data::Data()" << std::endl;
    }
    ~Data() {
        log << "in Data::~Data()" << std::endl;
    }
   
    void f() {
        ++x;
    }
    int x = 0;
};

template<typename T>
class A {
    // declared but not defined
    static Data<T> data;
public:
    A() {
        data.f();
    }
 };


int main(){
    A<int> aInt;
    std::cout << log.str();
}