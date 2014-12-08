#include <iostream>
#include <functional>
#include <numeric>
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

    explicit MappingTableHasher(int version)
    {
        implementation = version == 0
            ? &MappingTableHasher::terrible
            : version == 1
            ? &MappingTableHasher::goodLowBits
            : version == 2
            ? &MappingTableHasher::goodHighBits
            : nullptr;
    }
    
    std::size_t operator()(MappingKey const& key) const
    {
        return (this->*implementation)(key);
    }
    
    std::size_t terrible(MappingKey const& key) const
    {
        return 1;
    }
    
    std::size_t goodHighBits(MappingKey const& key) const
    {
        return std::size_t(key.offset) << (sizeof(std::size_t)*8-15);
    }
    
    std::size_t goodLowBits(MappingKey const& key) const
    {
        return std::size_t(key.offset);
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

template<typename M>
void checkMap(M const& map)
{
    typedef std::unordered_map<std::size_t,std::size_t> BucketCounts;
    BucketCounts counts;
    for (auto const& item : map)
        counts[map.bucket(item.first)]++;
//    for (auto const& item : counts)
//        std::cout << item.first << ": " << item.second << std::endl;
    std::cout << counts.size() << " buckets" << std::endl;
    
    // Find worst bucket count
    auto worstCount = std::accumulate(std::begin(counts), std::end(counts),
            BucketCounts::value_type::first_type(0),
    [](BucketCounts::value_type::first_type a, BucketCounts::value_type const& b)
    {
        return std::max(a, b.second);
    });
    std::cout << "worst bucket: " << worstCount << std::endl;
}

int main()
{
    for (int hasherVersion = 0; hasherVersion < 3; ++hasherVersion)
    {
        MappingTable t = MappingTable(8, MappingTableHasher(hasherVersion));
        
        for (uint32_t i = 0; i < 15000; ++i)
            t.insert({{i, 0x1000}, {nullptr, 0}});
        checkMap(t);
    }
}

