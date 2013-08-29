#include <iostream>
#include <thread>
 
using namespace std;
 
int main()
{
    thread th([](){ cout << "lol dongs" << endl; });
    th.join();
    return 0;
}