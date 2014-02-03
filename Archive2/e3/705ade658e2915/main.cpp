#include <deque>
#include <iostream>


using namespace std;

class R {
public:
    R(){};
    ~R(){};

    inline void queue(R* r) { neighbours.push_back(r); }
    inline R& getFirstNeighbour() { return *neighbours.front(); }

    virtual void printSomething() { cout << "R" << endl; }
protected:
    deque<R*> neighbours;
};

class RD: public R {
public:
    RD(){};
    ~RD(){};

    void printSomething() { cout << "RD" << endl; }
    void doSomethingElse();
};


int main()
{
R r;
//R with 3 neighbors
r.queue(new RD());


r.getFirstNeighbour().printSomething();


return 0;
}
