#include <string>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <memory>

using namespace std;

class A
{
    shared_ptr<A> parent;
    vector<weak_ptr<A> > children;
public:
    A() : name("I'm new")
    {}
    
    ~A(){
        cout<<name<<" died"<<endl;
    }
    string name;
    virtual void setParent(A *child){
        parent=shared_ptr<A>(child);
    }
    virtual void hello()
    {
        cout<<"i am "<<name<<endl;
      for(auto &i : children)
      {
        if(auto pi=i.lock()){
            pi->hello();
        }
      }
    }

};

class B : public A
{
    int numbers;
    virtual void hello(){
        A::hello();
         cout<<name<<" is a B!"<<endl;       
    }
    
};


int main(){
    auto a1= shared_ptr<A>(new B());
    auto a2= shared_ptr<A>(new A());
    auto a3= shared_ptr<A>(new B());
    
    a1->name="1";
    a2->name="2";
    a3->name="3";
    
    a2->setParent(a1.get());
    a3->setParent(a2.get());
      
    
//    shared_ptr<A*> a1=&a2;
    
    
    a1->hello();
   // a2= shared_ptr<A>(new A());
   // a1->hello();
    cout<<"done"<<endl;
    return 0;
}