#include <iostream>
using namespace std;

typedef void (*TFuncPtr)(void);

class Intern {
public:
    TFuncPtr m_ptr;
    Intern() { cout << "Intern()" << endl; }
    ~Intern() { m_ptr = NULL; cout << "~Intern()" << endl; }
};


template <class T>
class TBaseClass {
public:
    void Close() {};
    TBaseClass() {};
    virtual ~TBaseClass() {
        static_cast<T*>(this)->Close();
    }
};

static void Func() {
    cout << "Func" << endl;
}

class TDerived : public TBaseClass<TDerived> {
public:
    Intern m_intern;
    TDerived() {
        m_intern.m_ptr = Func;
    }
    void Close() {
        m_intern.m_ptr();
        cout << "TDerived::Close" << endl;
    }
};


int main() {
    TDerived *d = new TDerived();
    delete d;
    return 0;
}