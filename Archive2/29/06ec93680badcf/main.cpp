#include <string>
#include <boost/property_tree/ptree.hpp>

class data_holder
{
public:

    template <typename DATA_TYPE>
    void add_data(std::string section, std::string key, DATA_TYPE data)
    {
        if (section != "") section += ".";
        propertyTree.put(section + key, data);
    }

    boost::property_tree::ptree propertyTree;
};

struct Thing
{
    int ID;
    float f;
};

template<>
void data_holder::add_data(std::string section, std::string key, Thing data)

{
    auto sectionKey = section + key;
    propertyTree.put(sectionKey + "." + "ID", data.ID);
    propertyTree.put(sectionKey + "." + "f", data.f);
}

int main()
{
    data_holder dh;
    dh.add_data("section", "key", Thing{ 12, 3.4f });
}