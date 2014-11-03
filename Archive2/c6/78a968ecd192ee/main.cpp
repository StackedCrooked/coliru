#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/range/algorithm.hpp>
#include <iostream>
#include <cassert>

template <typename T>
using BoundShmemAllocator = boost::interprocess::allocator<T, boost::interprocess::managed_shared_memory::segment_manager>;

class MyStruct {
public:
    MyStruct() {};
    MyStruct ( int i ) : i ( i ) {};
    int i;
};

template <template<typename...> class BoundShmemAllocator>
using MyStructVector = boost::interprocess::vector<MyStruct, BoundShmemAllocator<MyStruct> >;

using HeapMyStructVector  = MyStructVector<std::allocator>;
using ShmemMyStructVector = MyStructVector<BoundShmemAllocator>;

template <typename Src, typename Dest>
void copy(Src const &src, Dest &des) {
    des.assign(src.begin(), src.end());
}

//
///////////////////////////////////////////////////////////////

int main() {
    srand ( time ( 0 ) );

    // A managed shared memory where we can construct objects
    boost::interprocess::managed_shared_memory segment = boost::interprocess::managed_shared_memory ( boost::interprocess::open_or_create, "MySharedMemory", 65536 );
    BoundShmemAllocator<int> const shmem_alloc ( segment.get_segment_manager() );

    ShmemMyStructVector *src = segment.find_or_construct<ShmemMyStructVector> ( "MyStruct" ) ( shmem_alloc );   
    for ( size_t i = 0; i < 5; i++ )  
		src->push_back(rand());

    // You can have something like this working:
    HeapMyStructVector des; // and also the shm stuff below
    des.push_back(rand());

    copy(*src, des);
    std::cout << "Shmem: ";
    for ( size_t i = 0; i < src->size(); i++ ) std::cout << i << ": " << src->at(i).i << (i!=src->size()-1?", ":"\n");
    std::cout << "Heap: ";
    for ( size_t i = 0; i < des.size(); i++ ) std::cout << i << ": " << des.at(i).i << (i!=des.size()-1?", ":"\n");

    segment.destroy<ShmemMyStructVector> ( "MyStruct" );
}