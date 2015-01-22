#include <iostream>
#include <string>

namespace ns {

// primitives
template<typename Algo>
void serialization(Algo algo, int& i)
{ algo.primitive(i); }

template<typename Algo>
void serialization(Algo algo, std::string& s)
{ algo.primitive(s); }

// Pairs
template<typename Algo, typename Item>
void serialization(Algo algo, const char* name, Item& item)
{
    algo.pair(name, item);
}

// iostream algos
struct iodeserialize {
    std::istream& in;
    
    void primitive(int& i)
    { in >> i; }
    
    void primitive(std::string& s)
    { in >> s; }
    
    template<typename Item>
    void pair(const char* name, Item& item)
    {
        // ironclad parsing right here
        in.ignore(std::string { name }.length() + sizeof " = " - 1);
        serialization(*this, item);
    }
};

struct ioserialize {
    std::ostream& out;
    
    void primitive(int i)
    { out << i; }
    
    void primitive(std::string const& s)
    { out << s; }
    
    template<typename Item>
    void pair(const char* name, Item& item)
    {
        out << name << " = ";
        serialization(*this, item);
    }
};

template<typename Item>
void ioread(std::istream& is, Item& item)
{ serialization(iodeserialize { is }, item); }

template<typename Item>
void iowrite(std::ostream& os, Item& item)
{ serialization(ioserialize { os }, item); }

/*** HERE ***/
struct udt {
    std::string name;
    int age;
};

template<typename Algorithm>
void serialization(Algorithm algo, udt& u)
{
    serialization(algo, "name", u.name);
    serialization(algo, "age", u.age);
}

struct udts {
    udt u, v, w;
};

template<typename Algorithm>
void serialization(Algorithm algo, udts& us)
{
    serialization(algo, us.u);
    serialization(algo, us.v);
    serialization(algo, us.w);
}

} // ns

int main()
{
    ns::udts us {};
    ns::ioread(std::cin, us);
    us.u.age += 2;
    ns::iowrite(std::cout, us);
}
