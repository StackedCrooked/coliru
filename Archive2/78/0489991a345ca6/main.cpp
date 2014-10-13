#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/string.hpp>

using namespace boost::interprocess;

typedef boost::interprocess::managed_shared_memory::segment_manager                    SegmentManager;
typedef boost::interprocess::allocator<char, SegmentManager>                           CharAllocator;
typedef boost::interprocess::basic_string<char, std::char_traits<char>, CharAllocator> ShmString;
typedef boost::interprocess::allocator<ShmString, SegmentManager>                      StringAllocator;
typedef boost::interprocess::vector<ShmString, StringAllocator>                        ShmStringVector;

int main ()
{
    //Remove shared memory on construction and destruction
    struct shm_remove
    {
        shm_remove() { shared_memory_object::remove("MySharedMemory"); }
        ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
    } remover;

    //Create shared memory
    managed_shared_memory segment(create_only,"MySharedMemory", 65536);

    //An allocator convertible to any allocator<T, SegmentManager> type
    StringAllocator alloc_inst (segment.get_segment_manager());

    //Construct the shared memory map and fill it
    ShmStringVector *my_ssvec = segment.construct<ShmStringVector> ("ShmStringVector")(alloc_inst);

    for (char ch : { 'a', 'b', 'c' })
        my_ssvec->emplace_back(200, ch, alloc_inst);
}
