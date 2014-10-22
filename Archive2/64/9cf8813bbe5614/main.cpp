// writer.cxx

#include <boost/interprocess/containers/map.hpp>
#include <functional>
#include <utility>

// ShmTypedefs.h

#ifndef __SHM_TYPE_DEFS__
#define __SHM_TYPE_DEFS__
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/containers/map.hpp>

//the strings also need to be assigned from the shared memory
typedef boost::interprocess::allocator<void, boost::interprocess::managed_shared_memory::segment_manager> VoidAllocator;
typedef boost::interprocess::allocator<char, boost::interprocess::managed_shared_memory::segment_manager> CharAllocator;
typedef boost::interprocess::basic_string<char, std::char_traits<char>, CharAllocator> SharedString;

//Note that map<Key, MappedType>'s value_type is std::pair<const Key, MappedType>,
//so the allocator must allocate that pair.
typedef boost::interprocess::allocator<std::pair<const SharedString, int>, boost::interprocess::managed_shared_memory::segment_manager > InnerMapAlloc;
typedef boost::interprocess::map<SharedString, int, std::less<SharedString>, InnerMapAlloc>  MappedType;

typedef SharedString KeyType;
typedef std::pair<const KeyType, MappedType> ValueType;

//allocator for the string
typedef boost::interprocess::allocator<SharedString, boost::interprocess::managed_shared_memory::segment_manager> StringAllocator;
//allocator of for the map.
typedef boost::interprocess::allocator<ValueType, boost::interprocess::managed_shared_memory::segment_manager> ShmemAllocator;
//third parameter argument is the ordering function is used to compare the keys.
typedef boost::interprocess::map<KeyType, MappedType, std::less<KeyType>, ShmemAllocator> MySHMMap;
#endif

#include <iostream>
using namespace boost::interprocess;

int main() {
    // remove earlier existing SHM
    shared_memory_object::remove("SharedMemoryName");

    // create new
    managed_shared_memory segment(create_only, "SharedMemoryName", 65536);

    // Initialize the shared memory STL-compatible allocator
    ShmemAllocator alloc_inst(segment.get_segment_manager());

    // offset ptr within SHM for map
    // After construction m_pmap will contain the only object that has been constructed in pmap[0]
    // If we construct another object it will goto pmap[1]

    offset_ptr<MySHMMap> m_pmap = segment.construct<MySHMMap>("MySHMMapName")(std::less<SharedString>(), alloc_inst);

    // Insert data in the map
    StringAllocator string_alloc_instance(segment.get_segment_manager());

    SharedString key("case1", string_alloc_instance);
    SharedString inner_map_key("inner_case1", string_alloc_instance);

    SharedString key1("case2", string_alloc_instance);
    SharedString inner_map_key1("inner_case2", string_alloc_instance);

    SharedString inner_map_key2("inner_case3", string_alloc_instance);

    InnerMapAlloc inner_map_alloc_instance(segment.get_segment_manager());

    {
        MappedType& tmp = m_pmap->emplace(key, MappedType(inner_map_alloc_instance)).first->second;
        tmp.emplace(inner_map_key, 2030);
        tmp.emplace(inner_map_key2, 2034);
    }

    {
        MappedType& tmp = m_pmap->emplace(key, MappedType(inner_map_alloc_instance)).first->second;
        tmp.emplace(inner_map_key1, 2031);
    }
    //std::cout << "\n " << m_pmap[0][key][inner_map_key] << std::endl;
    //std::cout << "\n " << m_pmap[0][key1][inner_map_key1] << std::endl;
    
    for (auto const& outer : *m_pmap)
        for (auto const& inner : outer.second)
            std::cout << outer.first << ", " << inner.first << ", " << inner.second << "\n";
}
