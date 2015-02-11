#include <iostream>
#include <string>

using namespace std;

class Test 
{
 private:
   int x;
   std::string name ;
 public:
    Test(int i) 
    {
        cout<<"Conversion constructor called..."<<endl;
        x = i;
        name = "default"; // default is the name
    }
    Test(int i, std::string str)
    {
        cout<<"Conversion constructor called..."<<endl;
        x = i;
        name = str; // custom name
    }
    ~Test()
    {
        cout<<"Destructor called..."<<endl;
    }
    void show() 
    { 
        cout<<"[" << name << "] x = "<<x<<endl; 
    }
};

int main()
{
  Test t(20, "MyNewObject");
  t.show();
  t = 30; 
  t.show();

  return 0;
}