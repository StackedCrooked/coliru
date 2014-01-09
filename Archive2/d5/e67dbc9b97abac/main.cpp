#include <vector>

#include <boost/interprocess/managed_mapped_file.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/named_recursive_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>

namespace bip = boost::interprocess;
using mutex_type = bip::named_mutex;

class CGLParam {};

typedef bip::allocator<CGLParam, bip::managed_shared_memory::segment_manager> ShmemAllocator;
typedef std::vector<CGLParam, ShmemAllocator> MyVector;

class Funcall
{
    std::vector<CGLParam> vecParams;
};


struct mutex_remove
{
    mutex_remove() { mutex_type::remove("2faa9c3f-4cc0-49c5-8f79-f99ce5a5d526"); }
    ~mutex_remove(){ mutex_type::remove("2faa9c3f-4cc0-49c5-8f79-f99ce5a5d526"); }
} remover;

static mutex_type mutex(bip::open_or_create,"2faa9c3f-4cc0-49c5-8f79-f99ce5a5d526");

class Global_Funcall
{
    MyVector* vecFuncalls;
    Global_Funcall()
    {
        bip::scoped_lock<mutex_type> lock(mutex);

        bip::shared_memory_object::remove("MySharedMemory");
        bip::managed_shared_memory segment(bip::create_only, "MySharedMemory", 65536);
        //Initialize shared memory STL-compatible allocator
        const ShmemAllocator alloc_inst(segment.get_segment_manager());

        //Construct a vector named "MyVector" in shared memory with argument alloc_inst
        vecFuncalls = segment.construct<MyVector>("MyVector")(alloc_inst);
    }

};

void InvokeFuncs(CGLParam *presult)
{
    bip::scoped_lock<mutex_type> lock(mutex);
    bip::managed_shared_memory open_segment(bip::open_only, "MySharedMemory");
    auto listParams = open_segment.find<MyVector>("MyVector").first;

    MyVector::const_iterator it;
    for (it = listParams->cbegin(); it != listParams->cend(); it++)
    {
        //it->InvokeFunc(presult);
    }

}

int main()
{
}
