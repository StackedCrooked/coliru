#include <iostream>
#include <memory>
#include <map>

typedef std::map<uint32_t, std::unique_ptr<uint32_t>  > ntohl_map_type;
typedef std::map<uint32_t, uint32_t> u32_map_type;

void
u32_map()
{
    uint32_t key(0);
    uint32_t val(0);
    u32_map_type u32_map;

    u32_map.insert(u32_map_type::value_type(key, val));
    u32_map.insert(std::pair<uint32_t, uint32_t>(++key, ++val));

    std::cout << "u32_map: " << std::endl;
    for (auto &itr : u32_map) {
        std::cout << itr.first << " = " << itr.second << "\n";
    }
    std::cout << std::endl;
}

void
uptr_map()
{
    uint32_t key(9);
    std::unique_ptr<uint32_t> u32_uptr1(new uint32_t(1));
    ntohl_map_type ntohl_map;

    ntohl_map.insert(ntohl_map_type::value_type(key, std::move(u32_uptr1)));

    ++key;
    std::unique_ptr<uint32_t> u32_uptr2(new uint32_t(1));

    ntohl_map.insert(ntohl_map_type::value_type(key, std::move(u32_uptr2)));

    std::cout << "uptr_map: " << std::endl;
    for (auto &itr : ntohl_map) {
        std::cout << itr.first << " = " << *itr.second << "\n";
    }
}

int
main()
{
    u32_map();
    uptr_map();

    return 0;
}
