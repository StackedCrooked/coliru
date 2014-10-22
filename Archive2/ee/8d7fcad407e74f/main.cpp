#include <iostream>
#include <thread>
#include <atomic>
#include <mutex>
#include <chrono>
#include <random>
using namespace std;
int g=1;
mutex m;
mutex go;

int il[5];
class Rnd {
    public:
    int operator()(int from, int to)
    {
        uniform_int_distribution<int>d(from,to);
        return d(engine);
    }
    Rnd()
    {
        engine.seed(chrono::system_clock::now().time_since_epoch().count());
    }
    protected:
    mt19937 engine;
} rnd;


void f()
{
    while(1)
    {
    m.lock();
    g+=2;
    m.unlock();
    int G=g;
    if (G > 20) return;
    bool OK = true;
    for(int i = 2; i *i <= G; i++)
        if (G%i ==0) { OK=false;break;}
        
    if (!OK) continue;
    go.lock();
    cout << G << " pierwsza" << endl;
    go.unlock();
 
}
    return;
}
int main()
{
 
	thread t1(f);
    thread t2(f);
    thread t3(f);
    thread t4(f);
    thread t5(f);
  
	t1.join();
        
	t2.join();
    t3.join();
    t4.join();
    t5.join();

	return 0;
}

