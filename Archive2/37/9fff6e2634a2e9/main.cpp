#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/list.hpp>
#include <boost/interprocess/managed_mapped_file.hpp>
#include <cassert>

typedef boost::interprocess::allocator<int, boost::interprocess::managed_mapped_file::segment_manager>
    ShmemAllocator; // Define an STL compatible allocator of ints that allocates from the managed_mapped_file. This allocator
                    // will allow placing containers in the segment
typedef boost::interprocess::vector<int, ShmemAllocator> MyVector; // Alias a vector that uses the previous STL-like allocator so
                                                                   // that allocates its values from the segment

typedef boost::interprocess::allocator<int, boost::interprocess::managed_mapped_file::segment_manager> ShmemListAllocator;
typedef boost::interprocess::list<int, ShmemListAllocator> MyList;

int main()
{
    // Construct managed_mapped_file shared memory
    std::remove("MySharedMemory");
    boost::interprocess::managed_mapped_file segment(boost::interprocess::create_only, "MySharedMemory", 65536);

    // const ShmemAllocator alloc_inst(segment.get_segment_manager());
    MyVector *instance  = segment.construct<MyVector>("MyType instance 1")(segment.get_segment_manager());
    MyVector *instance2 = segment.construct<MyVector>("MyType instance 2")(segment.get_segment_manager());
    MyList   *instance3 = segment.construct<MyList>  ("MyList instance")(segment.get_segment_manager());

    assert(instance);
    assert(instance2);
    assert(instance3);

    assert(!std::equal_to<void*>()(instance,  instance2));
    assert(!std::equal_to<void*>()(instance,  instance3));
    assert(!std::equal_to<void*>()(instance2, instance3));
}
