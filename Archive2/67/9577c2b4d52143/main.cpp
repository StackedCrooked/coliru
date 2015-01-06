#include <iostream>

struct test {
    const int x;
    test(int number): x(number) {}
};

int main()
{
    test* t;
    if(false) {
        t = new test(5);
    } else {
        t = new test(8);
    }
    
    //t->x = 10; //toggle this comment and you will get an error
    std::cout << t->x << "\n";
    
    return 0;
}
