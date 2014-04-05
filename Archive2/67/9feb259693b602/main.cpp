#include <string>

template <typename> struct Property { std::string value; };

namespace tag
{
    struct name;
    struct address;
    struct city;    
}

typedef Property<tag::name>    Name;
typedef Property<tag::address> Address;
typedef Property<tag::city>    City;

struct Contact
{
    void set(Name    v) { _name    = v.value; }
    void set(Address v) { _address = v.value; }
    void set(City    v) { _city    = v.value; }
  private:
    std::string n,a,c;
}

int main()
{
    Contact c;
    c.set(Address("Sample Blvd. 42"));
}