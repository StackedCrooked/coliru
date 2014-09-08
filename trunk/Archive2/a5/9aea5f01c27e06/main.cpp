#include <vector>
#include <cstdio>

struct A
{
    A():m_copy(false) {}
    virtual void copy(A& a) { printf("Can't do that fool"); }
    
    bool m_copy;
};

struct B : public A
{
    B():A() {m_copy = true;}
    virtual void copy(A& b) override {} // I want to be copy(B& b)
};

struct C : public A
{
    // Don't have copy, use the A
};

int main()
{
    std::vector<A> vector;

    A a;
    B b;
    C c;
    
    
    B toCopy;
    
    vector.push_back(a);
    vector.push_back(b);
    vector.push_back(c);
    
    for(int i=0; i < 3; ++i)
    {
        if (vector[i].m_copy)
            vector[i].copy(toCopy);
    }
    
    return 0;
};