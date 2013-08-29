#include <iostream>
#include <thread>
#include <algorithm>
#include <list>
 struct MyData { public: bool IsDone() { return false; } };

 struct functor
    {
    public:
        bool operator()(MyData& mydata)
        { 
           return mydata.IsDone();
        }   
    };
    
    void removeIfDone(std::list<MyData>& myList)
    {
       std::list<MyData>::iterator it =
         remove_if(myList.begin(), myList.end(), 
             functor()); //call operator() on functor
         myList.erase(it, myList.end());
    }


int main()
{

}