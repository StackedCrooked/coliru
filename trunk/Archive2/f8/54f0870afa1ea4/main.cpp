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
};



struct AbstractSchedule : virtual AbstractObject
{
    AbstractSchedule()
    {
        std::cout << "AbstractSchedule: " << mRemoteId << std::endl;
    }

    virtual ~AbstractSchedule() {}

    void setInitialTimeToWait(int64_t ns) { ns_ = ns; }

    int64_t ns_ = 0;
};


template<typename T>
struct Schedule : AbstractSchedule, Object<T>
{
    Schedule()
    {
        std::cout << "Schedule: " << mRemoteId << std::endl;
    }

    virtual void prepare() = 0;

    virtual void destroy()
    {

    }

};


struct RequestPageSchedule : Schedule<RequestPageSchedule>
{
    void prepare()
    {

    }

};



int main()
{
    auto a = new RequestPageSchedule();

    RequestPageSchedule::GetById<RequestPageSchedule>(a->getRemoteId());
    AbstractSchedule::GetById<AbstractSchedule>(a->getRemoteId());


}
