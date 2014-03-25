#include <exception>

namespace exception
{
  struct MyException : public std::exception
  {};
}


struct AnotherException : public exception::MyException
{
    using MyException::MyException;
};


int main() {
}