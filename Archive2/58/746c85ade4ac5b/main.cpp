#include <iostream>
using namespace std;

class foo {};

class parent
{
public:
   parent(foo* f){}
   parent(){}
};

class child : public parent
{
public:
   child():parent(new foo()) //Not allowed as we are passing a temporary - Undefined reference error
      {}
};

int main() {
    // your code goes here
	return 0;
}