#include <iostream>
#include <chrono>

class Test
{
    using std::chrono::microseconds;
    
public:
    Test() : ms(0) { }

private:
    microseconds ms;
};




int main()
{
    Test test;
        
    return 0;
}
