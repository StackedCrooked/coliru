#include <iostream>

#include <boost/mpl/vector.hpp>
#include <boost/mpl/for_each.hpp>

struct Example
{
    int id;
    std::string name;
};

// single property inside struct
template<int Tag>
struct EntityProperty
{
};

template<>
struct EntityProperty<0>
{
    typedef int ValueType;
    
    constexpr static const char* name = "id";
    constexpr static const auto value = &Example::id;
};

template<>
struct EntityProperty<1>
{
    typedef std::string ValueType;
    
    constexpr static const char* name = "name";
    constexpr static const auto value = &Example::name;
};

// metadata about struct
template<typename EntityClass>
struct Entity
{
};

template<>
struct Entity<Example>
{
    // this one below must be changed, EntityProperty<int> should be created 'on the fly' with
    // some more template/macro magic
    typedef boost::mpl::vector<
        EntityProperty<0>,
        EntityProperty<1>
    > Properties;
    
    constexpr static const char* name = "Example";
};


template<typename T>
struct EntityPropertyPrinter
{
    EntityPropertyPrinter(const T& object) : object(object)
    {
    }

    template<typename Tag>
    void operator()(const Tag&)
    {
        std::cout << "+ property(" << Tag::name << ", " << object.*(Tag::value) << ")\n";
    }
    
    const T& object;
};

template<typename EntityClass>
void print(const EntityClass& ex)
{
    std::cout << "className(" << Entity<EntityClass>::name << ")\n";
    EntityPropertyPrinter<EntityClass> printer(ex);
    boost::mpl::for_each<typename Entity<EntityClass>::Properties>(printer);
}

int main()
{
    const Example ex { 666, "satan" };
    print(ex);

    return 0;
}