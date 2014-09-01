#include <thread>

struct MyClass { };

void th(MyClass *&p)
{
    while(p!=NULL)
    {
    }
}

using namespace std;

int main()
{
    MyClass *m = new MyClass();
    thread t1(th,m);

    delete m;
    m=NULL;
    t1.join();
}
