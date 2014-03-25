#include <exception>

namespace exception
{
  struct MyException : public std::exception
  {};
}


struct AnotherException : public exception::MyException
{
    AnotherException() : MyException() { }
};


int main() {
}