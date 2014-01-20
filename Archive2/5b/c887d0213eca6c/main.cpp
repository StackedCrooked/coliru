#include <iostream>
using namespace std;

class Progression
{
public:
    Progression()
    {
        cur=first=0;
    }
    Progression(long f)
    {
        cur=first = f;
    }
    void printProgression(int n)
    {
        cout<<firstValue();
        for(int i=0;i<=n; i++)
        {
            cout<<' '<<nextValue();
        }
    }
    virtual ~Progression() {}
protected:
    long first;
    long cur;

    virtual long firstValue()
    {
        cur= first;
        return cur;
    }
    virtual long nextValue()
    {
        return cur++;
    }
};

class ArithProgression :public Progression
{
public:
    ArithProgression(long i=1)
    :Progression()
    {
        inc=i;
    }
    virtual ~ArithProgression () {}
protected:
    long inc;
    virtual long nextValue()
    {
        cur+=inc;
        return cur;
    }
private:
};

int main()
{
    Progression* p;
    p= new ArithProgression();
    p->printProgression(10);
    delete p;
}