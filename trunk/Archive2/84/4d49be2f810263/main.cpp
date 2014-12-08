#include <iostream>
#include <functional>
#include <unordered_map>

struct MappingKey
{
    std::uint32_t offset;
    std::uint32_t length;
};

struct MappingValue
{
    void *address;
    uint64_t refcount;
};

struct MappingTableHasher
{
    std::size_t (MappingTableHasher::*implementation)(MappingKey const& key) const;

    explicit MappingTableHasher(bool goodLow)
    {
        implementation = goodLow
            ? &MappingTableHasher::goodLowBits
            : &MappingTableHasher::goodHighBits;
    }
    
    std::size_t operator()(MappingKey const& key) const
    {
        return (this->*implementation)(key);
    }
    
    std::size_t goodHighBits(MappingKey const& key) const
    {
        return 1;// std::size_t(key.offset) << (sizeof(std::size_t)*8-15);
    }
    
    std::size_t goodLowBits(MappingKey const& key) const
    {
        return 1;//std::size_t(key.offset);
    }
};

struct MappingTableComparer
{
    bool operator()(MappingKey const& a, MappingKey const& b) const
    {
        return a.offset == b.offset && a.length == b.length;
    }
};

typedef std::unordered_map<
    MappingKey,
    MappingValue,
    MappingTableHasher,
    MappingTableComparer
> MappingTable;

int main()
{
    MappingTable t = MappingTable(8, MappingTableHasher(true));
    
    for (uint32_t i = 0; i < 15000; ++i)
    {
        t.insert({{i, 0x1000}, {nullptr, 0}});
    }
    std::cout << t.load_factor() << std::endl;
    
    t = MappingTable(8, MappingTableHasher(false));
    
    for (uint32_t i = 0; i < 15000; ++i)
    {
        t.insert({{i, 0x1000}, {nullptr, 0}});
    }
    std::cout << t.load_factor() << std::endl;
    
}

