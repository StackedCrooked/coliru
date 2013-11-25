#include <iostream>
#include <thread>

using namespace std;

void Threadfun()
{
    cout<<"Thread function"<<endl;
}

int main()
{
    thread t1(Threadfun);
    //t1.join();
    
    return 0;
    
}
