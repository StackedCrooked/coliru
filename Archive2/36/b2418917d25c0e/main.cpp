#include <iostream>
#include <memory>
#include <string>

class citizen
{
private:
    std::string name;
    std::string nationality;
public:
    citizen(
            std::string const& name = "No name is given", 
            std::string const& nationality = "No nationality is given")
        : name(name),
          nationality(nationality)
    {
    }

    friend std::ostream& operator<<(std::ostream& os, citizen const& c)
    {
        return os 
         << "Name: "        << c.name        << std::endl
	     << "Nationality: " << c.nationality << std::endl;
    }

    citizen(const citizen &obj) 
	: name(obj.name),
          nationality(obj.nationality)
    {
    }
};

int main()
{
    citizen obj1;
    citizen obj2("Ali", "Pakistani");
    citizen obj3 = obj2;
    std::cout << obj1;
    std::cout << obj2;
    std::cout << obj3;
}
