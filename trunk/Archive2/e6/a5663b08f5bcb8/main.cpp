#include <string>
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace pt = boost::property_tree;
namespace jsp = pt::json_parser;

class Serializable
{
public:
    virtual ~Serializable() {}
    virtual void write(pt::ptree&, const std::string&) = 0;
    virtual boost::any read(pt::ptree&, const std::string&) = 0;
};

template<typename T>
class ClassicSerializable : public Serializable
{
public:
    ClassicSerializable(const T& value_) : value(value_) {}
    void write(pt::ptree& pt, const std::string& name)
    {
        pt.put(name, value);
    }
    boost::any read(pt::ptree& pt, const std::string& name)
    {
        return pt.get<T>(name);
    }
private:
    T value;
};

int main()
{
    pt::ptree tree;
    std::unique_ptr<Serializable> object(new ClassicSerializable<std::string>("value"));
    object->write(tree, "name");
    const std::string value = boost::any_cast<std::string>(object->read(tree, "name"));
    std::cout << value << std::endl;
}