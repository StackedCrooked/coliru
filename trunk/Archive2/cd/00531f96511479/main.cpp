#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <algorithm>
 
using namespace std;
 
class A
{
private:
    string m_memberA;
 
public:
    explicit A(string inp):m_memberA(inp){}
    int GetValue()
    {
        return m_memberA.size();
    }
};
 
class B
{
private:
    int m_memberB;
public:
    explicit B(int inp):m_memberB(inp){}
};
 
class C
{
private:
    double m_memberC;
public:
    explicit C(double inp):m_memberC(inp){}

    double GetValue()
    {
        return m_memberC; 
    }
};

 
template<typename Argument> 
class functor
{
private:
    Argument m_member;
public:
 
    functor(Argument a)
        : 
            m_member(a)
    {}

    template<typename PairIterator>
    bool operator()(PairIterator iter) const
    {
        return (m_member->GetValue() == (iter.first)->GetValue());
    }
};

template<typename Argument>
functor<Argument> make_functor(Argument const & a)
{
    return functor<Argument>(a); 
}
 
int main(int argc, char *argv[])
{
    A* obj_ptr_A1 = new A("Hello");
    A* obj_ptr_A2 = new A("MyWorld");
 
    B* obj_ptr_B1 = new B(22);
    B* obj_ptr_B2 = new B(11);
 
    C* obj_ptr_C1 = new C(5.5);
    C* obj_ptr_C2 = new C(9.5);
   
    map<A*, B*> myMap1;
    myMap1.insert(make_pair(obj_ptr_A1, obj_ptr_B1));
    myMap1.insert(make_pair(obj_ptr_A2, obj_ptr_B2));
 
    map<A*, C*> myMap2;
    myMap2.insert(make_pair(obj_ptr_A1, obj_ptr_C1));
    myMap2.insert(make_pair(obj_ptr_A2, obj_ptr_C2));

    map<C*, A*> myMap3;
    myMap3.insert(make_pair(obj_ptr_C1, obj_ptr_A1));
    myMap3.insert(make_pair(obj_ptr_C2, obj_ptr_A2));
   
    if(find_if(myMap1.begin(), myMap1.end(), make_functor(obj_ptr_A2)) != myMap1.end())
    {
        cout << "Found" << endl;
    }
 
    if(find_if(myMap2.begin(), myMap2.end(), make_functor(obj_ptr_A2)) != myMap2.end())
    {
        cout << "Found" << endl;
    }
 
    if(find_if(myMap3.begin(), myMap3.end(), make_functor(obj_ptr_C1)) != myMap3.end())
    {
        cout << "Found" << endl;
    }

 
    return 0;
}
