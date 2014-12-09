#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/string.hpp>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>

namespace sehe
{
    template < typename T1, typename T2, typename Alloc1, typename Alloc2 >
        struct mutable_pair
        {
            typedef T1 first_type;
            typedef T2 second_type;

            mutable_pair( Alloc1 alloc ) : first( T1( alloc ) ), second( T2( alloc ) ) {}
            mutable_pair( const T1 & f, const T2 & s ) : first( f ), second( s ) {}
            mutable_pair( const std::pair< T1, T2 > & p ) : first( p.first ), second( p.second ) {}

            T1         first;
            mutable T2 second;
        };


    template <typename KeyType, typename ValueType, typename Compare, typename KeyAllocator, typename ValueAllocator, typename Element = mutable_pair< KeyType, ValueType, KeyAllocator, ValueAllocator > >
        struct map_gen
        {
            typedef boost::multi_index::multi_index_container
            <
                Element,
                boost::multi_index::indexed_by
                <
                    boost::multi_index::ordered_unique< boost::multi_index::member< Element, KeyType, &Element::first >, Compare >
                >,
                typename KeyAllocator::template rebind<Element>::other
            > type;
        };

    typedef struct {
        template <typename T, typename U> bool operator()(const T &t, const U &u) const { return t < u; }
    } Comparator;

}

// Typedefs of allocators and containers
namespace Shared
{
    typedef boost::interprocess::managed_shared_memory Segment;
    typedef boost::interprocess::managed_shared_memory::segment_manager SegmentManager;
    typedef boost::interprocess::allocator<void, SegmentManager> Allocator;


    typedef boost::interprocess::allocator<char, SegmentManager> CharAlloc;
    typedef boost::interprocess::basic_string<char, std::char_traits<char>, CharAlloc> String;
    typedef boost::interprocess::allocator< String, SegmentManager > StringAlloc;

    typedef boost::interprocess::allocator< int, SegmentManager > IntAlloc;
    typedef boost::interprocess::vector< int, IntAlloc > IntVector;
    typedef boost::interprocess::allocator< IntVector, SegmentManager > IntVectorAlloc;

    typedef sehe::map_gen< String, String,    sehe::Comparator, StringAlloc, StringAlloc >::type StringStringMap;
    typedef sehe::map_gen< String, IntVector, sehe::Comparator, StringAlloc, IntVectorAlloc >::type StringIntVectorMap;
}

int main(void) {
    struct shm_remove {
        shm_remove() { boost::interprocess::shared_memory_object::remove("MySharedMemory"); }
        ~shm_remove() { boost::interprocess::shared_memory_object::remove("MySharedMemory"); }
    } remover;

    // Create shared memory
    Shared::Segment seg(boost::interprocess::create_only, "MySharedMemory", 65536);
    Shared::Allocator alloc(seg.get_segment_manager());

    // Construct the shared memory map
    Shared::StringIntVectorMap *myMapPtr = seg.construct<Shared::StringIntVectorMap>("myMap")(alloc);

    myMapPtr->emplace(Shared::String("foo", alloc), Shared::IntVector(alloc));
    myMapPtr->emplace(Shared::String("goo", alloc), Shared::IntVector(alloc));
    myMapPtr->emplace(Shared::String("hoo", alloc), Shared::IntVector(alloc));

    // This the only version I can get to work.  But it forces you to create a
    // copy of the key you are searching for, in the managed segment.
    Shared::String key("foo", alloc);     

    // This is the point of the exercise:
    auto it = myMapPtr->find(key);

    if (it!=myMapPtr->end())
        std::cout << "Found: '" << it->first << "' -> '" << it->second.size() << "'\n";

    // this is now okay too
    char szkey[] = "foo";
    it = myMapPtr->find(szkey);
    if (it!=myMapPtr->end())
        std::cout << "Found: '" << it->first << "' -> '" << it->second.size() << "'\n";

    // this is now okay too
    std::string skey("foo");
    it = myMapPtr->find(skey.c_str());
    if (it!=myMapPtr->end())
        std::cout << "Found: '" << it->first << "' -> '" << it->second.size() << "'\n";

    return 0;
}
