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
    void set(Name    v) { n = v.value; }
    void set(Address v) { a = v.value; }
    void set(City    v) { c = v.value; }
  private:
    std::string n,a,c;
};

int main()
{
    Contact c;
    c.set(Address { "Sample Blvd. 42" });
}