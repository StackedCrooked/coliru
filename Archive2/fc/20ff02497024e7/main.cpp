//#include <boost/range.hpp>
#include <boost/interprocess/managed_mapped_file.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/unordered_map.hpp>

namespace bip = boost::interprocess;
// ShmString is boost::interprocess::basic_string
typedef bip::managed_mapped_file segment_t; // managed_shared_memory
typedef bip::allocator<char, segment_t::segment_manager> CharAllocator;
typedef bip::basic_string<char, std::char_traits<char>, CharAllocator> ShmString;
typedef ShmString HashKeyType;
// ComplexType is a wrapper for internal interprocess::map
struct ComplexType {
    typedef bip::allocator<std::pair<int const, int>, segment_t::segment_manager> Alloc;
    typedef bip::map<int, int, std::less<int>, Alloc> Map;

    template <typename Alloc2>
    ComplexType(std::string, Alloc2 const& alloc = {}) : map(alloc) {}
    Map map;
};

typedef ComplexType HashMappedType;
typedef std::pair<const ShmString, ComplexType> HashValueType;
typedef bip::allocator<HashValueType, segment_t::segment_manager> HashMemAllocator;
typedef boost::unordered_map<HashKeyType, HashMappedType, boost::hash<HashKeyType>, std::equal_to<HashKeyType>, HashMemAllocator>
    TestHashMap;

int main()
{
    // Allocation:
    {
        segment_t segment(bip::open_or_create, "MySharedMemory", 65536);
        auto thm_ = segment.construct<TestHashMap>("TestHashMap")(3, boost::hash<ShmString>(), std::equal_to<ShmString>(),
                segment.get_allocator<HashValueType>());

    }
    // Usage:
    segment_t segment(bip::open_only, "MySharedMemory");
    auto thm_ = segment.construct<TestHashMap>("TestHashMap")(3, boost::hash<ShmString>(), std::equal_to<ShmString>(), segment.get_allocator<HashValueType>());
    ShmString str("123.345", segment.get_allocator<ShmString>());

    ComplexType th("MySharedMemory", segment.get_segment_manager());

    HashValueType value(str, th);
    thm_->insert(value);
}
