#include <iostream>
#include <string>
#include <vector>

#define ECHO(v) std::cout << v << std::endl;

using std::string;

class Logger;

class BaseService
{
    friend class Logger;
    
private:
    string baseDataPrivate;
        
protected:
    string baseDataProtected;
        
public:
    string baseDataPublic;
    
    BaseService() {
        baseDataPrivate   = "bazis adat privat";
        baseDataProtected = "bazis adat vedett";
        baseDataPublic    = "bazis adat publikus";
    }
};

class Service : public BaseService
{
private:
    string dataPrivate;
    
protected:
    string dataProtected;

public:
    string dataPublic;

protected:
    class Logger
    {
    public:
        Logger() = delete;
        static void log(Service*);
    };

public:
    Service();
    void handleEvent();
};

Service::Service() {
    dataPublic    = "adat publikus";
    dataProtected = "adat vedett";
    dataPrivate   = "adat privat";
}

/*class Logger
{
public:
    static void log(Service*);
};*/

void Service::handleEvent() {
    Logger::log(this);
}

void Service::Logger::log(Service* s) {
    ECHO(s->dataPublic);
    ECHO(s->dataProtected);
    ECHO(s->dataPrivate);
    
    ECHO(s->baseDataPublic);
    ECHO(s->baseDataProtected);
    ECHO(s->baseDataPrivate);
}

int main() {
    Service s;
    s.handleEvent();
}
