#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class AbstractBase
{
    public:
        virtual bool IsDerived1() const { return false; }
        virtual void Print() const = 0;
        virtual ~AbstractBase(){}
};

class Derived1 : public AbstractBase
{
    public:
        virtual bool IsDerived1() const { return true; }
        virtual void Print() const { cout << "Derived1" << endl; }
};

class Derived2 : public AbstractBase
{
    public:
        virtual void Print() const { cout << "Derived2" << endl; }
};

// This funtion returns the elements of v that are of type Derived1.
vector<Derived1*> SelectDerived1(const vector<AbstractBase*>& v)
{
    vector<Derived1*> derived1s;

#define USE_COPY_IF 0

#if USE_COPY_IF
    // attempt to use copy_if - does not compile:
    //     /usr/include/c++/4.7/bits/stl_algo.h:990:6:
    //     error: invalid conversion from 'AbstractBase*' to 'Derived1*'
    //     [-fpermissive]
    copy_if(v.begin(), v.end(), derived1s.begin(),
            [](AbstractBase* elem){ return elem->IsDerived1(); });
#else
    for (auto it = v.begin(); it != v.end(); ++it)
        if ((*it)->IsDerived1())
            derived1s.push_back(static_cast<Derived1*>(*it));
#endif

    return derived1s;
}

int main()
{
    vector<AbstractBase*> v;
    Derived1* d1 = new Derived1;
    Derived2* d2 = new Derived2;
    v.push_back(d1);
    v.push_back(d2);

    vector<Derived1*> derived1s = SelectDerived1(v);
    for (auto it = derived1s.begin(); it != derived1s.end(); ++it)
        (*it)->Print();

    delete d1;
    delete d2;

    return 0;
}

