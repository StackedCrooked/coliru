#include <iostream>
#include <functional>

struct Foo {
    void print_add(int i){ 
      std::cout << i << '\n'; 
    }
};

typedef std::function<void(int)> fp;

void test(fp my_func)
{
  my_func(5);
}

int main(){
    Foo foo;
    test(std::bind(&Foo::print_add, &foo, std::placeholders::_1));
    test([&foo](int i){ foo.print_add(i); });
    return 0;
}
