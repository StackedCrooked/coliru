#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/string.hpp>

#include <boost/container/scoped_allocator.hpp>

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>

namespace emulation {
    template <typename T1,typename T2,typename Alloc>
        struct mutable_pair
        {
            typedef Alloc allocator_type;
            typedef T1 first_type;
            typedef T2 second_type;

            mutable_pair(Alloc alloc):first(T1(alloc)),second(T2(alloc)){}
            mutable_pair(const T1& f,const T2& s):first(f),second(s){}
            mutable_pair(const std::pair<T1,T2>& p):first(p.first),second(p.second){}

            template <typename U, typename V, typename Alloc2>
            mutable_pair(const U& f,const V& s, Alloc2 alloc):first(f, alloc),second(s, alloc){}

            T1         first;
            mutable T2 second;
        };

    using namespace boost::multi_index;

    template <typename Key, typename T, typename Compare, typename Allocator, typename Element = mutable_pair<Key, T, Allocator> >
        using map = multi_index_container<
            Element,
            indexed_by<
                ordered_unique<member<Element,Key,&Element::first>,Compare>
            >,
            typename Allocator::template rebind<Element>::other
        >;

  template <typename Key, typename T, typename Compare, typename Allocator, typename Element = mutable_pair<Key, T, Allocator> >
    using multimap = multi_index_container<
        Element,
        indexed_by<
            ordered_non_unique<member<Element,Key,&Element::first>,Compare>
        >,
        typename Allocator::template rebind<Element>::other
    >;

  template <typename Key, typename T, typename Compare, typename Allocator> 
      struct wrap_map : map<Key, T, Compare, Allocator> {
          typedef map<Key, T, Compare, Allocator> base_type;
          typedef typename base_type::template nth_index<0>::type index_type;

          wrap_map(Allocator alloc) : base_type({}, alloc)
          { 
          }

          wrap_map(Compare cmp, Allocator alloc) : base_type(
                  typename base_type::ctor_args_list{
                    typename index_type::ctor_args { typename index_type::key_from_value {}, cmp }
                  },
                  alloc)
          { 
          }
      };
}


// Typedefs of allocators and containers
namespace Shared {
    typedef boost::interprocess::managed_shared_memory Segment;
    typedef Segment::segment_manager SegmentManager;
    typedef boost::container::scoped_allocator_adaptor<boost::interprocess::allocator<void, SegmentManager> > Allocator;

    typedef Allocator::rebind<char>::other CharAllocator;
    typedef boost::interprocess::basic_string<char, std::char_traits<char>, CharAllocator> String;

    struct MyLess {
        template <typename T, typename U> bool operator()(const T &t, const U &u) const { return t < u; }
    };
    typedef MyLess StringComparator;

    typedef emulation::mutable_pair<String, String, CharAllocator> MapItem;
    typedef Allocator::rebind<MapItem>::other MapItemAllocator;
    typedef emulation::wrap_map<String, String, StringComparator, MapItemAllocator> Map;
}

int main(void) {
    struct shm_remove {
        shm_remove() { boost::interprocess::shared_memory_object::remove("MySharedMemory"); }
        ~shm_remove() { boost::interprocess::shared_memory_object::remove("MySharedMemory"); }
    } remover;

    // Create shared memory
    Shared::Segment seg(boost::interprocess::create_only, "MySharedMemory", 65536);
    Shared::Allocator alloc(seg.get_segment_manager());

    // An instance of the string comparator, to construct the map
    Shared::StringComparator cmp;

    // Construct the shared memory map
    Shared::Map *myMapPtr = seg.construct<Shared::Map>("myMap")(cmp, alloc);

    myMapPtr->emplace("foo", "bar");
    myMapPtr->emplace("goo", "car");
    myMapPtr->emplace("hoo", "dar");

    // This the only version I can get to work.  But it forces you to create a
    // copy of the key you are searching for, in the managed segment.
    Shared::String key("foo", alloc);     
    
    // This is the point of the exercise:
    auto it = myMapPtr->find(key);

    if (it!=myMapPtr->end())
        std::cout << "Found: '" << it->first << "' -> '" << it->second << "'\n";

    // this is now okay too
    char szkey[] = "foo";
    it = myMapPtr->find(szkey);
    if (it!=myMapPtr->end())
        std::cout << "Found: '" << it->first << "' -> '" << it->second << "'\n";

    // this is now okay too
    std::string skey("foo");
    it = myMapPtr->find(skey.c_str());
    if (it!=myMapPtr->end())
        std::cout << "Found: '" << it->first << "' -> '" << it->second << "'\n";

    return 0;
}
