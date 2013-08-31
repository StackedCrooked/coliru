#include <cstdio>
#include <iostream>
#include <thread>
using namespace std;

void f()
{
    for(int i=0;i<0;i++)
    {
        printf("%d\n", i);
    }
}



int main()
{
    thread p(f);
    thread q(f);
    p.join();
    q.join();
    
}
