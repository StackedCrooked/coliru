#include <stdio.h>
#include <memory>

std::unique_ptr<int> p(new int(3));

std::unique_ptr<int> foo()
{
return p;
}

int main()
{
foo();
//std::unique_ptr<int> p2 = p; //2
}