#include <iostream>
#include <memory>

struct cls{
    ~cls(){std::cout<<"dtor\n";}
};

void foo(cls** pp){
    *pp = new cls;
}

std::unique_ptr<cls> foo()
{
  cls *p = nullptr;
  foo(&p);
  return std::unique_ptr<cls>{p};
}

int main()
{
    auto pp = foo();
}