#include <iostream>
#include <string>
#include <vector>

class A {
public:
    int i;
};

int 
main()
{
    int i[2] = {42, 42};
    
    A *a = new(&i[0]) A();
    std::cout << a->i << '\n';
    
    A *b = new(&i[1]) A;
    std::cout << b->i << '\n';
}
