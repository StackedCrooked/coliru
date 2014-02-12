#include <iostream>
#include <thread>
#include <functional>
#include <chrono>

void ThreadFunction(bool& blnFinish) {
    int intIterationCount = 0;
    while (!blnFinish) {
        intIterationCount += 1;
        std::this_thread::yield();
    }
    std::cout<<"Ran for "<<intIterationCount<<" iterations before being asked to stop"<<std::endl;
}

int main()
{
    bool blnStopThread = false;
    std::thread tfuncExampleThread(&ThreadFunction,std::ref(blnStopThread));
    std::this_thread::sleep_for(std::chrono::nanoseconds(1));
    blnStopThread = true;
    tfuncExampleThread.join();
}
