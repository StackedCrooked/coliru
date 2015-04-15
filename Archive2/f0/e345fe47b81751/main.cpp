#include <iostream>
#include <string>
#include <vector>

#define ECHO(v) std::cout << v << std::endl;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec) {
    for (auto& el : vec)
        os << el << ' ';
    return os;
}

/* class A
{
public:
    virtual ~A() = 0;
    virtual void asd() = 0;
};

inline A::~A() {
}

void A::asd() {
    ECHO("A::asd()");
}

class B : public A
{
public:
    //~B() = delete;
    
    void asd() {
        A::asd();
        ECHO("B::asd()");
    }
}; */

class AA
{
public:
    AA() = default;
    virtual ~AA() = 0;
};

inline AA::~AA() {
    ECHO("AA::~AA");
}

class BB : public AA
{
public:
    BB() = default;
    virtual ~BB() {
        ECHO("BB::~BB")
    };
    
    static void staticTechno() {
        ECHO("STATIC TECHNO!");
    }
    
    void techno() {
        ECHO("TECHNO!");
    }
};

void call_static(void (*fn)()) {
    (*fn)();
}

template <class T>
void call_member(T* obj, void (T::*fn)()) {
    (obj->*fn)();
}

class Service
{
private:
    std::string dataPrivate;
    
protected:
    std::string dataProtected;

public:
    std::string dataPublic;

protected:
    class Logger
    {
    public:
        Logger() = delete;
        static void log(Service*);
    };

public:
    Service();
    void callLogger();
};

Service::Service() {
    dataPublic = "publikus adat";
    dataProtected = "vedett adat";
    dataPrivate = "privat adat";
}

/*class Logger
{
public:
    static void log(Service*);
};*/

void Service::callLogger() {
    Logger::log(this);
}

void Service::Logger::log(Service* s) {
    ECHO(s->dataPublic);
    ECHO(s->dataProtected);
    ECHO(s->dataPrivate);
}

int main()
{
    Service s;
    s.callLogger();
    
    AA* aabb = new BB();
    delete aabb;
    
    call_static(&BB::staticTechno);
    
    BB bb = BB();
    call_member(&bb, &BB::techno);
    
    std::string str;
    const char* pcstr = str.c_str();
    str = pcstr;
    //ECHO(str);
    
    /* std::vector<std::string> words = {
        "Hello", "from", "GCC", __VERSION__, "!"
    };
    std::cout << words << std::endl; */
}
