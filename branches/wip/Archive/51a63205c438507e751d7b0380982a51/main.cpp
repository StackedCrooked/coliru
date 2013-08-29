#include <iostream>
#include <thread>
#include <vector>
#include<iterator>


class time
{
    public:
    time();
    void foo();
};

time::time()
{
}

void time::foo()
{
    std::cout << "foo";
}

int main()
{
    time t;
    t.foo();
}