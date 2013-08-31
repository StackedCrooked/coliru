#include <iostream>
#include <thread>
using namespace std;
void hello();
int main()
{
    std::cout << "Hello GCC " << __VERSION__ << "!" << std::endl;
    std::thread t([](){ std::cout << "Hello Thread!"; });
    hello();
    t.join();
}


void hello(){
    
    cout<< "bad editors";
    
}