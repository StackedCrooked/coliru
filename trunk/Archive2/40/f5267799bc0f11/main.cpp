#include <string>
#include <deque>
#include <vector>
#include <iostream>
using namespace std;

class Provider
{
public:
    string name;
    Provider( string name ) : name(name) {}
    Provider( const char * name ) : name(name) {}
};

template <class T>
class Vec : public std::vector<T>
{
private:
    Vec(){}
public:
    Vec(int upperbound, int lowerbound)
    {
        ub = upperbound;
        lb = lowerbound;
        this->resize(ub-lb+1);
    }

public:
    T& operator[] (int idx)
    {
        return this->at(idx - lb);
    }

    private:
        int ub;
        int lb;
};

int main()
{
    int upperBound = 175642;
    int lowerBound = 175000;

    // I want a Vec of deques<Provider> index such that idx [0] is starting at lowerbound
    Vec<std::deque<Provider>> vecOfDeq(upperBound, lowerBound);

    //Here, fill the Vec<std::deque<Provider>> with some random examples
    vecOfDeq[175000].push_back("John Q. Public");
    vecOfDeq[175000].push_back("Joe Blow");
    vecOfDeq[175000].push_back("Joe six-pack");
    std::cout << vecOfDeq[175000].at(1).name << std::endl; // Vec[175000] is really Vec[0]

    return 0;
}