#include <iostream>
#include <vector>

#include <cstdlib>
#include <ctime>
#include <inttypes.h>

using namespace std;

template<typename T>
struct Id
{
    static uintptr_t id() 
    {
        return reinterpret_cast<uintptr_t>(&id);
    }
};

template<typename T>
uintptr_t getId()
{
    return Id<T>::id();
}

//////

class Base 
{
public:
    Base(int key) : m_value(0), m_key(key) {}
    
    int getKey()   const { return m_key; }
    int getValue() const { return m_value; }

    void debug() const
    {
        cout << m_key << ':' << m_value << endl;
    }

protected:
    uintptr_t m_value;

private:
    int m_key;

};

template<typename T>
class Derived : public Base
{
public:
    Derived(int key) : Base(key) { m_value = getId<T>(); }
};

//////

void foo(const Base& clazz)
{
    Base clazz2 = clazz; // truncate type here
    clazz2.debug();    
}

int main()
{
    // simulating memory randomizing
    {
        srand(time(0));
        unsigned char *buf = new unsigned char[1024];
        for (size_t i = 0; i < 1024; ++i)
        {
            buf[i] = (unsigned char)(rand() % 256);
        }
        delete buf;
    }

    cout << "int id: " << getId<int>() << endl;

    foo(Base(1));
    foo(Derived<int>(2));
   
    return 0;
}
