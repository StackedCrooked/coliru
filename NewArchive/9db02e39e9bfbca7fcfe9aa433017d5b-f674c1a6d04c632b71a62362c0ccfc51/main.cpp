#include <iostream>
#include <string>
#include <vector>
#include <thread>

using namespace std;

void f(const char* s)
{
    for (int i = 0; i < 100; i++)
    {
        printf("%s %d\n, s, i");
        if(i%20 == 0)
        {
            this_thread::yield();
        }
    }
}

int main()
{
    thread p(bind(f, "hola"));
    thread q(f, "bye");
    p.join();
    q.join();
}
