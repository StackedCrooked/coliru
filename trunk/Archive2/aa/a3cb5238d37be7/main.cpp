#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/tag.hpp>
#include <boost/multi_index/member.hpp>

#include <iostream>

using namespace boost::multi_index;

// UGLY IMITATION OF JSONWriter class - do NOT judge ...
class JSONWriter
{
public:
    JSONWriter() : comma(false) { }
    void String(const std::string& txt)
    {
        std::cout << "\"" << txt << "\"";
        
        if (comma)
            std::cout << ",";
        else
            std::cout << ":";
        
        comma = !comma;
    }
    
    void StartObject()
    {
        if (comma)
            std::cout << ",";
        std::cout << "{";
        comma = false;
    }
    
    void StartArray()
    {
        std::cout << "[";
        comma = false;
    }
    
    void EndObject()
    {
        std::cout << "}";
        comma = true;
    }
    
    void EndArray()
    {
        std::cout << "]";
        comma = true;
    }
    
    bool comma;
};

class RapidJsonHierarchyVisitor
{
public:
    RapidJsonHierarchyVisitor(JSONWriter& out)
        : out_(out)
    {
    }
    
    void beginType(const std::string& type)
    {
        out_.StartObject();
        
        out_.String("type");
        out_.String(type);
            
        out_.String("children");
        out_.StartArray();
    }
    
    void endType(const std::string& type)
    {
        out_.EndArray();
        out_.EndObject();
    }
    
private:
    JSONWriter& out_;
};

struct DeviceType
{
    std::string type;
    std::string baseType;
};

class DeviceHierarchy
{
    struct TypeIndex {};
    struct BaseTypeIndex {};
    
public:
    void addDeviceType(const DeviceType& type)
    {
        container_.insert(type);
    }
    
    template<typename Visitor>
    void serialize(Visitor& visitor, const std::string& rootType) const
    {
        visitor.beginType(rootType);
        
        auto iters = container_.get<BaseTypeIndex>().equal_range(rootType);
        for (auto it = iters.first; it != iters.second; it++)
            serialize(visitor, it->type);
        
        visitor.endType(rootType);
    }
    
private:
    typedef multi_index_container<
        DeviceType,
        indexed_by<
            hashed_unique<
                tag<TypeIndex>,
                member<DeviceType, std::string, &DeviceType::type>
            >,
            hashed_non_unique<
                tag<BaseTypeIndex>,
                member<DeviceType, std::string, &DeviceType::baseType>
            >
        >
    > DeviceTypeContainerType;
    
    DeviceTypeContainerType container_;
};

int main()
{
    DeviceHierarchy container;
    container.addDeviceType(DeviceType{"actor",            "device"});
    container.addDeviceType(DeviceType{"sensor",           "device"});
    container.addDeviceType(DeviceType{"actor",            "device"});
    container.addDeviceType(DeviceType{"binarySwitch",     "actor"});
    container.addDeviceType(DeviceType{"multilevelSwitch", "binarySwitch"});
    container.addDeviceType(DeviceType{"binarySensor",     "sensor"});
    container.addDeviceType(DeviceType{"multilevelSensor", "sensor"});
    
    JSONWriter out;
    RapidJsonHierarchyVisitor x(out);
    container.serialize(x, "device");
}