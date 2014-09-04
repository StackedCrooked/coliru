#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include <iostream>
#include <list>
using namespace std;

class MyClass
{
  public:
    std::string productCode_;
    void setProductCode()
    {
        productCode_ = "123472797AB";
    }
    
    std::string getProductCode()
    {
        return productCode_;
    }
};

int fun()
{
    list<int> myIntVector;
    list<int>::iterator myIntVectorIterator;

    // Add some elements to myIntVector
    //myIntVector.push_back(1);
    //myIntVector.push_back(4);
    myIntVector.push_back(8);

    myIntVectorIterator = myIntVector.begin();

    //if(myIntVectorIterator != myIntVector.end())
    return *myIntVectorIterator;
    //else
    //    return 666;
}

int main()
{
    //cout << fun();
    int pt = 5;
    int * ptr = new(pt);
    
    cout << *ptr;
    delete ptr;
}




