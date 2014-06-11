
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <memory>
#include <type_traits>
#include <string>

using namespace std;
using std::vector;

class Base
{
private:
    vector <float> protectedElement;
public:
    inline vector<float> getVector()
    {
        return protectedElement;
    }
    inline void setVector(float v)
    {
        protectedElement.push_back(v);
    }
    
    Base(float v=0)
    {
        setVector(v);
    }
    
    void Look()
    {
        vector<float>::iterator it;
        for(it=getVector().begin(); it!=getVector().end(); it++)
        {
            cout << *it << endl;
        }
    }
};

class Derived : public Base
{
public:
    //inline Derived(vector <float> v): Base(v)
    inline Derived(float v=0.0): Base(v)
    {

    }
};

int main()
{
    Base elemento;
    
    elemento.setVector(0);
    elemento.setVector(2);
    elemento.setVector(4);
    
    
}