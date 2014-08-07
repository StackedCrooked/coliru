#include <iostream>
#include <string>
#include <vector>
#include <mutex>

struct StateMachine
{
    void onStart()
    {
    }
}

class Padre
{
    public: 
    void start()
    {
        stateMachine.onStart();
        start_();
    }
    
    protected:
    virtual void _start() = 0;
}

classe Figlio : public Padre
{
    private:
    void _start()
    {
        // do something
    }
}


int main()
{
 Padre* p = new Figlio;
 
 delete p;
 return 0;
}
