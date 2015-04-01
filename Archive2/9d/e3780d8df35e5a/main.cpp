#include <iostream>
#include <future>

using namespace std;

void foo()
{
    cout<<"In foo"<<endl;
    cout<<"Sleeping for 1 seconds"<<endl;
    this_thread::sleep_for(chrono::seconds(1));
    cout<<"Returning from foo"<<endl;
    return;
}


int main()
{
    cout <<"Starting foo on different thread"<<endl;
    future<void> f0=async(launch::async,foo);
    cout<<"Sleeping for 999 milliseconds"<<endl;
    this_thread::sleep_for(chrono::milliseconds(999));
    cout<<"In main"<<endl;
    cout<<"Returning from main"<<endl;
    return 0;
}
