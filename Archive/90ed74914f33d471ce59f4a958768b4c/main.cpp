#include <iostream>
#include <thread>
#include <vector>
#include<iterator>

namespace x {
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
} // namespace x

int main()
{
    x::time t;
    t.foo();
}