#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <cstdint>

struct name_val_struct
{
    std::string name;
    std::int8_t value1;
	std::uint8_t value2;
	std::uint8_t value3;

    bool operator==(const name_val_struct& req) const
    {
        std::cout << "bool operator==" << std::endl;
        return req.name == name;
    }

    bool operator>(const name_val_struct& req) const
    {
        if (req.name != name)
            return name > req.name;
        
        if (value3 != req.value3)
        {
            if (value1 != req.value1)
            {
                return value2 > req.value2;
            }

            return value1 < req.value1;
        }

        return value3 > req.value3;
    }

    name_val_struct(const std::string& _name) : name(_name) {}
    name_val_struct(const std::string& _name, std::int8_t _value1, std::uint8_t _value2, std::uint8_t _value3)
        : name(_name), value1(_value1), value2(_value2), value3(_value3)
    {}
};

int main()
{
    std::set<name_val_struct, std::greater<name_val_struct>> requests;
    requests.insert(name_val_struct("name1", 1, 2, 3));
    requests.insert(name_val_struct("name2", 4, 5, 6));
    requests.insert(name_val_struct("name3", 7, 8, 9));
    requests.insert(name_val_struct("name4", 11, 12, 13));

    std::cout << requests.size() << std::endl;

    requests.insert(name_val_struct("name1", 10, 2, 3));

    std::cout << requests.size() << std::endl;

    requests.erase(name_val_struct("name1"));
    std::cout << requests.size() << std::endl;

    std::cout << std::boolalpha << (name_val_struct("name1") == name_val_struct("name1", 1, 2, 3)) << std::endl;
}
