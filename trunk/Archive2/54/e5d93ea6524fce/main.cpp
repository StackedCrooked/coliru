#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

mutex m;
int  count = 0;
#define COUNT_DONE  10

void functionCount(const char* name)
{
   for(;;)
   {
        m.lock();
        auto c = ++count;
        m.unlock();

        cout << "Counter value " << name << ": " << c << endl;
        if(c >= COUNT_DONE)
                return;
    }
}

int main()
{
    thread t1(functionCount, "functionCount1"), t2(functionCount, "functionCount2");
    t1.join();
    t2.join();
}