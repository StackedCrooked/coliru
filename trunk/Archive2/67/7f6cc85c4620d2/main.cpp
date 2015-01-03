#include <iostream>
#include <unordered_set>

template<std::size_t size>
struct InverseGoldenRatio
{
};

template<>
struct InverseGoldenRatio<4>
{
    static constexpr std::size_t value = 0x9e3779b9;
};

template<>
struct InverseGoldenRatio<8>
{
    static constexpr std::size_t value = 0x9E3779B97F4A7C15;
};

template<typename T>
void hash_combine(std::size_t& hash, T incoming)
{
    hash ^= std::hash<T>()(incoming) + 
        InverseGoldenRatio<sizeof(std::size_t)>::value +
        (hash << 6) + (hash >> 2);
}

// =============

struct MappingKey
{
    float x, y, z;
};

// Hash table for quick lookup of existing mappings
// Keyed on offset and length, value is refcount and address
struct MappingTableHasher {
    std::size_t operator()(MappingKey const& a) const
    {
        std::size_t hash = 0;
        hash_combine(hash, a.x);
        hash_combine(hash, a.y);
        hash_combine(hash, a.z);
        return hash;
    }
};
struct MappingTableComparer {
    bool operator()(MappingKey const& a, MappingKey const& b) const
    {
        return a.x == b.x && a.y == b.y && a.z == b.z;
    }
};
typedef std::unordered_set<
    MappingKey,
    MappingTableHasher,
    MappingTableComparer
> MappingTable;

int main()
{
    MappingTable table;
    
    std::cout << table.insert({1,2,3}).second << std::endl; // 1
    std::cout << table.insert({1,2,3}).second << std::endl; // 0
    std::cout << table.insert({1,2,3}).second << std::endl; // 0
    std::cout << table.insert({2,2,3}).second << std::endl; // 1
    std::cout << table.insert({3,2,3}).second << std::endl; // 1
    std::cout << table.insert({2,2,3}).second << std::endl; // 0
    std::cout << table.insert({3,2,3}).second << std::endl; // 0
}
