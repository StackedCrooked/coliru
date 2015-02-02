#include <iostream>
#include <thread>
#include <chrono>

volatile bool start;
volatile bool stopped;
int f(){
    int a=0;
    while(start){
        ++a;
    }
    std::cout << a << std::endl;
    stopped=true;
    return 0;
}

void perform(){
    std::thread t(f);
    t.detach();
}
int main()
{
    start=true;
    stopped=false;
    perform();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    start=false;
    std::cout << stopped << std::endl;
    
    std::this_thread::sleep_for(std::chrono::seconds(1));
    start=false;
    std::cout << stopped << std::endl;
    std::cout << "Finished!" << std::endl;
}
