#include <iostream>
#include <string>

class Caller;

class Wrapper // to C function
{
    public:
        static void readObject(Caller* theCaller);
        static void callbackReadObject(void *data);
    private:
        static Caller* pCaller;
};

class Caller
{
    public:
        typedef void (Caller::*CbkPtr_t)(void*);
        void readObject(CbkPtr_t cbFcnt)
        {
            cbkFunction = cbFcnt;
            Wrapper::readObject(this);
        }

        void callbackReadObject(void *data)
        {
            (this->*cbkFunction)(data);
        }

    private:
        CbkPtr_t cbkFunction;
};
 
Caller* Wrapper::pCaller;

void read(void (*pf)(void*)) {
    pf(nullptr);
}

void Wrapper::readObject(Caller* theCaller)
{
    pCaller = theCaller;
    read(&Wrapper::callbackReadObject);
}

void Wrapper::callbackReadObject(void *data)
{
    pCaller->callbackReadObject(data);
}


class A : public Caller
{
    int member = 42;
public:
    void req()
    {
        //readObject(&A::specializedCallback); // error from compiler
        readObject(static_cast<Caller::CbkPtr_t>(&A::specializedCallback)); // has error during excecution, because of downcast?
    }

    void specializedCallback(void *data) {
        std::cout << "Successfull call to " <<  __PRETTY_FUNCTION__ << ' ' << data << ", member = " << member << std::endl;
    }
};


int main()
{
    A a;
    a.req();
}