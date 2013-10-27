#include <iostream>
#include <thread>
#include <chrono>
using namespace std; 
void foo()
{
    // simulate expensive operation
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
 
void bar()
{
    // simulate expensive operation
    std::this_thread::sleep_for(std::chrono::seconds(1));
}
class A{
    public:
    void funcion(string a, int b){cout << a << "-> "<<b<<endl;}    
      
};
 
int main()
{
    std::cout << "starting first helper...\n";
    std::thread helper1(foo);
 
    std::cout << "starting second helper...\n";
    std::thread helper2(bar);
    
    cout << "start yo px" << endl;
    thread helper3(A::funcion,"En ",10);
 
    std::cout << "waiting for helpers to finish..." << std::endl;
    helper1.join();
    helper2.join();
 
    std::cout << "done!\n";
}