#include <iostream>
#include <exception>
using namespace std;

class stack_error : public std::exception
{
 public:
  virtual const char* what() const throw();
  stack_error(string const& m) throw(); //noexpect;
  ~stack_error() throw();
  string message;
 private:
};

class stack_full_error : public stack_error
{
 public:
  stack_full_error(string const& m) throw();
  ~stack_full_error() throw();
  virtual const char* what() const throw();
};

class stack_empty_error : public stack_error
{
 public:
  stack_empty_error(string const& m) throw();
  ~stack_empty_error() throw();
  virtual const char* what() const throw();
};

stack_error::stack_error(string const& m) throw()
: exception(), message(m)
{
}

stack_error::~stack_error() throw()
{  
}

const char* stack_error::what() const throw()
{
  return message.c_str();
}

stack_full_error::stack_full_error(string const& m) throw() 
  : stack_error(m)
{   
}

stack_full_error::~stack_full_error() throw()
{

}

const char* stack_full_error::what() const throw()
{
  return message.c_str();
}

stack_empty_error::stack_empty_error(string const& m) throw() 
  : stack_error(m)
{   
}

stack_empty_error::~stack_empty_error() throw()
{

}

const char* stack_empty_error::what() const throw()
{
  return message.c_str();
}

int main()
{

        throw stack_full_error("Stack is full!");

    return 0;
}