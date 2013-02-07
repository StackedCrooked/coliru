#include <iostream>
#include <thread>
class cTEst
{
    public:
    
};
int main()
{
    std::cout << "Hello GCC " << __VERSION__ << "!" << std::endl;
    std::thread t([](){ std::cout << "Hello Thread!"; });
    t.join();
}