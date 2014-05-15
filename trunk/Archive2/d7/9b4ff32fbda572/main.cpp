#include <iostream>
#include <map>
#include <string>
#include <functional>
#include <utility>

using namespace std;

double fakeComputation()
{
    return 1.35;
}

struct SomeKindOfException
{
    
};

class DataStore
{
public:
   void bindData()
   {
      properties.clear();
      InsertProperty("param1", &DataStore::param1);
      InsertProperty("param2", &DataStore::param2);
      InsertProperty("value1", fakeComputation());
      InsertProperty("value2", fakeComputation());
   }

   double Get(const string& name)
   {
       auto it = properties.find(name);
       if (it != end(properties))
           return it->second(); // ora diventa una function call 
       throw SomeKindOfException();
   } 
   
   void Set(const string& name, double value)
   {
       auto it = properties.find(name);
       if (it != end(properties))
           it->second() = value;
       else throw SomeKindOfException();
    }
    
    void printMembers()
    {
        cout << "param1 = " << param1 << endl;
        cout << "param2 = " << param2 << endl;
    }

private:
    typedef double DataStore::*DataStorePtrToMember;

    void InsertProperty(string key, DataStorePtrToMember memPtr)
    {
	    properties.insert({move(key), [=]() -> double& {
	    	return this->*memPtr;
	    }});
    }

    struct Property 
    {
        double& operator()() { return value; }
        double value;
    };

    void InsertProperty(string key, double value)
    {
    	properties.insert({move(key), Property{value}});
    }

   double param1 = 0.1;
   double param2 = 0.2;
   map<string, function<double&()>> properties;

};

int main()
{
   DataStore ds; ds.bindData();
   ds.printMembers();
   ds.Set("param1", 10);
   ds.printMembers();
}
