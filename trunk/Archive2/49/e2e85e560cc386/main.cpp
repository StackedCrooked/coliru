#include <iostream>
#include <map>
#include <sstream>
#include <string>

typedef std::string RemoteId;

struct AbstractObject
{
    AbstractObject() : mRemoteId(GenerateUniqueId())
    {
        std::cout << "AbstractObject: " << mRemoteId << std::endl;

    }

    virtual ~AbstractObject() {}

    const RemoteId& getRemoteId() const { return mRemoteId; }
    
    void destroy();

    typedef std::map<std::string, AbstractObject*> Map;

    static Map& GetMap()
    {
        static Map fMap;
        return fMap;
    }

    template<typename T>
    static T& GetById(const RemoteId& id)
    {
        auto it = GetMap().find(id);
        if (it == GetMap().end())
        {
            throw std::runtime_error("Not found.");
        }

        std::cout << "GetById: found object with id: " << it->second->mRemoteId << std::endl;

        return dynamic_cast<T&>(*it->second);
    }

    static RemoteId GenerateUniqueId()
    {
        static int i = 1;
        std::stringstream ss;
        ss << i++;
        return ss.str();
    }
    
    virtual void do_destroy() = 0;

    std::string mRemoteId;
};

template<typename T>
struct Object : virtual AbstractObject
{
    Object() :
        AbstractObject()
    {
        std::cout << "Object: " << mRemoteId << std::endl;
        GetMap().insert(std::make_pair(getRemoteId(), this));
    }
    
    static T& GetById(const RemoteId& id) { return AbstractObject::GetById<T>(id); }
};



struct HTTPClient : Object<HTTPClient>
{
    void do_destroy()
    {
    }
};



struct AbstractSchedule : virtual AbstractObject
{
    virtual ~AbstractSchedule() {}
    
    static AbstractSchedule& GetById(const RemoteId& id)
    {
        return AbstractObject::GetById<AbstractSchedule>(id);
    }

    void setInitialTimeToWait(int64_t ns) { ns_ = ns; }

    void prepare() { do_prepare(); }
    
    void start() { do_start(); }
    
    void stop() { do_stop(); }
    
private:
    virtual void do_prepare() = 0;
    virtual void do_start() = 0;
    virtual void do_stop() = 0;
    
    int64_t ns_ = 0;
};


template<typename T>
struct Schedule : AbstractSchedule, Object<T>
{
    Schedule()
    {
        std::cout << "Schedule: " << this->mRemoteId << std::endl;
    }
    
    using Object<T>::GetById;
};


struct RequestPageSchedule : Schedule<RequestPageSchedule>
{
    void do_destroy() {}
    
    void do_prepare() {}
    void do_start() {}
    void do_stop() {}
};



int main()
{
    auto http = new HTTPClient();
    HTTPClient::GetById(http->getRemoteId());

    auto a = new RequestPageSchedule();
    RequestPageSchedule::GetById(a->getRemoteId());
    AbstractSchedule::GetById(a->getRemoteId());


}
