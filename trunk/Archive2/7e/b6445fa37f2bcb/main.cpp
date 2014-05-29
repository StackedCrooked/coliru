
#include <string>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <memory>

using namespace std;

class A
{
    shared_ptr<A> *ptr;
    weak_ptr<A> parent;

    vector<weak_ptr<A> > children;
public:
    A() : ptr(0), name("I'm new")
    {

    }

    virtual ~A() {
        parent.reset();
        cout<<name<<" died"<<endl;
    }
    string name;
    shared_ptr<A> & getPtr()
    {
        if(!ptr) {
            ptr=new shared_ptr<A>(this);
        }
        return *ptr;
    }

    virtual void setParent(shared_ptr<A> &par) 
    {

        parent=par;
        par.get()->children.push_back(weak_ptr<A>(getPtr()));
    }
    virtual void hello()
    {
        cout<<"i am "<<name<<endl;
        for(auto &i : children)
        {
            if(auto pi=i.lock()) {
                pi->hello();
            }
        }
    }

};

class B : public A
{
public:
    int numbers;
    ~B() {
        cout<<name<<" died (B!)"<<endl;
    }
    virtual void hello() {
        A::hello();
        cout<<name<<" is a B!"<<endl;
    }

};


int main() {
    A a1,a2,a3;

    a1.name="1";
    a2.name="2";
    a3.name="3";

    a2.setParent(a1.getPtr());
    a3.setParent(a2.getPtr());


//    shared_ptr<A*> a1=&a2;


    a1.hello();
//    a2.reset();
    cout<< ("removing a2") << endl;
    a2= A();

    a1.hello();
    cout<<("done") << endl;
    return 0;
}

