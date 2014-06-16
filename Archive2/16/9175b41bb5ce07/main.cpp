#include <iostream>

struct base
{
  virtual ~base() = 0;
};
base::~base() {}

struct derived : base
{};


int main() 
{
    base *b = new derived;
}
